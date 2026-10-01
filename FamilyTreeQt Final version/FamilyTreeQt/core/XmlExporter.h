#pragma once

#include <QXmlStreamWriter>
#include <QIODevice>
#include <QSet>

#include "Person.h"

// Writes a family tree to XML. Spouses are written as a reference
// element (full attributes, but no nested children) rather than
// being recursively expanded again, avoiding infinite mutual
// recursion between spouses -- same approach as the console
// version's writeXML(), extended with enough attributes that
// XmlImporter can fully reconstruct the spouse, not just their name.
class XmlExporter
{
public:

    static bool exportTree(Person* root, QIODevice* device)
    {
        if(root == nullptr || device == nullptr)
            return false;

        QXmlStreamWriter writer(device);
        writer.setAutoFormatting(true);
        writer.setAutoFormattingIndent(2);

        writer.writeStartDocument();
        writer.writeStartElement("FamilyTree");

        QSet<Person*> visited;
        writePerson(writer, root, visited);

        writer.writeEndElement();
        writer.writeEndDocument();

        return !writer.hasError();
    }

private:

    static void writeAttributes(QXmlStreamWriter& writer, Person* person)
    {
        writer.writeAttribute("id", QString::number(person->id()));
        writer.writeAttribute("name", person->name());
        writer.writeAttribute("gender", person->gender() == Gender::Male ? "male" : "female");
        writer.writeAttribute("status", person->status() == LifeStatus::Alive ? "alive" : "deceased");

        if(person->birthYear() > 0)
            writer.writeAttribute("birthYear", QString::number(person->birthYear()));

        if(person->deathYear() > 0)
            writer.writeAttribute("deathYear", QString::number(person->deathYear()));
    }

    static void writePerson(QXmlStreamWriter& writer, Person* person, QSet<Person*>& visited)
    {
        if(person == nullptr || visited.contains(person))
            return;

        visited.insert(person);

        writer.writeStartElement("Person");
        writeAttributes(writer, person);

        if(person->spouse() != nullptr)
        {
            writer.writeStartElement("Spouse");
            writeAttributes(writer, person->spouse());
            writer.writeEndElement();
        }

        QList<Person*> children = person->children();

        if(!children.isEmpty())
        {
            writer.writeStartElement("Children");

            for(Person* child : children)
                writePerson(writer, child, visited);

            writer.writeEndElement();
        }

        writer.writeEndElement();
    }
};
