#pragma once

#include <QXmlStreamReader>
#include <QIODevice>
#include <QHash>
#include <QList>
#include <QString>

#include "Person.h"
#include "FamilyForest.h"
#include "Relationships.h"

// Reads a file written by XmlExporter and reconstructs the family
// tree it describes into `forest`, returning the new root Person
// (already registered as a tree) or nullptr on failure.
//
// Import happens in two stages: first the whole document is parsed
// into a lightweight ParsedPerson tree (no Person objects yet),
// then that structure is "materialized" into real Person objects
// and relationships. Two stages because a person's spouse reference
// carries its own full attributes but no id we can trust to be
// unique against people already in this session's FamilyForest --
// everyone gets a *new* sequential id when materialized, and the
// parsed tree is what lets us wire relationships up correctly
// afterward regardless of the order things appeared in the file.
class XmlImporter
{
public:

    static Person* importTree(FamilyForest* forest, QIODevice* device, QString* errorMessage = nullptr)
    {
        if(forest == nullptr || device == nullptr)
        {
            if(errorMessage) *errorMessage = "Nothing to import from.";
            return nullptr;
        }

        QXmlStreamReader reader(device);
        ParsedPerson* parsedRoot = nullptr;

        while(!reader.atEnd() && !reader.hasError())
        {
            if(reader.readNext() == QXmlStreamReader::StartElement &&
               reader.name() == QStringLiteral("FamilyTree"))
            {
                while(reader.readNextStartElement())
                {
                    if(reader.name() == QStringLiteral("Person"))
                    {
                        parsedRoot = parsePerson(reader);
                        break;
                    }

                    reader.skipCurrentElement();
                }

                break;
            }
        }

        if(reader.hasError())
        {
            if(errorMessage) *errorMessage = "XML parse error: " + reader.errorString();
            delete parsedRoot;
            return nullptr;
        }

        if(parsedRoot == nullptr)
        {
            if(errorMessage) *errorMessage = "No <Person> found in this file -- is it a Family Tree export?";
            return nullptr;
        }

        Person* newRoot = materialize(forest, parsedRoot);

        if(newRoot != nullptr)
            forest->registerTree(newRoot);

        delete parsedRoot;

        return newRoot;
    }

private:

    // A person's spouse is parsed as a nested, ownership-holding
    // ParsedPerson too (it just never has children of its own) --
    // no shared/global lookup table needed, since the reference
    // travels structurally with the person who has it.
    struct ParsedPerson
    {
        QString name;
        Gender gender = Gender::Male;
        LifeStatus status = LifeStatus::Alive;
        int birthYear = 0;
        int deathYear = 0;
        ParsedPerson* spouse = nullptr;
        QList<ParsedPerson*> children;

        ~ParsedPerson()
        {
            delete spouse;
            qDeleteAll(children);
        }
    };

    static Gender parseGender(const QString& value)
    {
        return value.compare("female", Qt::CaseInsensitive) == 0 ? Gender::Female : Gender::Male;
    }

    static LifeStatus parseStatus(const QString& value)
    {
        return value.compare("deceased", Qt::CaseInsensitive) == 0 ? LifeStatus::Deceased : LifeStatus::Alive;
    }

    // Reads the attributes shared by both <Person> and <Spouse>
    // elements (id is intentionally not kept -- everyone gets a
    // fresh id when materialized into real Person objects).
    static ParsedPerson* readAttributesOnly(QXmlStreamReader& reader)
    {
        ParsedPerson* p = new ParsedPerson();

        QXmlStreamAttributes attrs = reader.attributes();
        p->name = attrs.value("name").toString();
        p->gender = parseGender(attrs.value("gender").toString());
        p->status = parseStatus(attrs.value("status").toString());
        p->birthYear = attrs.value("birthYear").toInt();
        p->deathYear = attrs.value("deathYear").toInt();

        return p;
    }

    // Parses a <Person> element (already positioned on its
    // StartElement), including its optional <Spouse> and <Children>,
    // consuming through its matching EndElement.
    static ParsedPerson* parsePerson(QXmlStreamReader& reader)
    {
        ParsedPerson* person = readAttributesOnly(reader);

        while(reader.readNextStartElement())
        {
            if(reader.name() == QStringLiteral("Spouse"))
            {
                person->spouse = readAttributesOnly(reader);
                reader.skipCurrentElement();
            }
            else if(reader.name() == QStringLiteral("Children"))
            {
                while(reader.readNextStartElement())
                {
                    if(reader.name() == QStringLiteral("Person"))
                        person->children.append(parsePerson(reader));
                    else
                        reader.skipCurrentElement();
                }
            }
            else
            {
                reader.skipCurrentElement();
            }
        }

        return person;
    }

    static Person* buildPerson(FamilyForest* forest, ParsedPerson* parsed)
    {
        Person* person = forest->createPerson(parsed->name, parsed->gender);
        person->setStatus(parsed->status);
        person->setBirthYear(parsed->birthYear);
        person->setDeathYear(parsed->deathYear);
        return person;
    }

    static Person* materialize(FamilyForest* forest, ParsedPerson* parsed)
    {
        if(parsed == nullptr)
            return nullptr;

        Person* person = buildPerson(forest, parsed);

        if(parsed->spouse != nullptr)
        {
            Person* spousePerson = buildPerson(forest, parsed->spouse);

            if(person->gender() == Gender::Male && spousePerson->gender() == Gender::Female)
                Relationships::connectSpouses(person, spousePerson);
            else if(person->gender() == Gender::Female && spousePerson->gender() == Gender::Male)
                Relationships::connectSpouses(spousePerson, person);
            // Two same-gender "spouse" entries in an imported file are
            // left unlinked rather than silently coerced -- the rest
            // of the import still proceeds normally.
        }

        for(ParsedPerson* child : parsed->children)
        {
            Person* childPerson = materialize(forest, child);
            Relationships::establishParentRelationship(childPerson, person);
        }

        return person;
    }
};
