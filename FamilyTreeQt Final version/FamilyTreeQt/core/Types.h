#pragma once

// Pure, dependency-free result and status codes.
// This mirrors the enums from the original console application
// (FamilyTree.cpp) exactly, so the validation *rules* we already
// built and tested carry over unchanged -- only the I/O is gone.

enum class Result
{
    Success,
    PersonNull,
    PersonNotFound,
    PersonDeceased,
    InvalidGender,
    SamePerson,
    AlreadyExists,
    DuplicateChild,
    DuplicateRelation,
    TreeAlreadyExists,
    RelationshipNotAllowed,
    CycleDetected,
    AncestorMarriage,
    Cancelled,
    UnknownError
};

enum class Gender
{
    Male,
    Female
};

enum class LifeStatus
{
    Alive,
    Deceased
};

// Human-readable text for a Result, used by both the console
// fallback and any QML error toast/snackbar.
inline const char* resultMessage(Result result)
{
    switch(result)
    {
        case Result::Success:                return "Operation completed successfully.";
        case Result::PersonNull:              return "Person does not exist.";
        case Result::PersonNotFound:          return "Person not found.";
        case Result::PersonDeceased:          return "This person is deceased.";
        case Result::InvalidGender:           return "Invalid gender for this relationship.";
        case Result::SamePerson:              return "A person cannot be related to themself.";
        case Result::AlreadyExists:           return "This relationship already exists.";
        case Result::DuplicateChild:          return "This child is already registered.";
        case Result::DuplicateRelation:       return "Duplicate relationship.";
        case Result::TreeAlreadyExists:       return "A family tree already exists for this person.";
        case Result::RelationshipNotAllowed:  return "This relationship is not allowed.";
        case Result::CycleDetected:           return "This would create a cycle: a person can't be their own ancestor or descendant.";
        case Result::AncestorMarriage:        return "This would marry two direct blood relatives (an ancestor and a descendant).";
        case Result::Cancelled:               return "Operation cancelled.";
        case Result::UnknownError:            return "An unknown error occurred.";
    }
    return "";
}
