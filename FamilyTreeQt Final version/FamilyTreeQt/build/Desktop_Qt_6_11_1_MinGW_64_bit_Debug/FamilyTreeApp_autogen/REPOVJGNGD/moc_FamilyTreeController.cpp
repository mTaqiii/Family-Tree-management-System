/****************************************************************************
** Meta object code from reading C++ file 'FamilyTreeController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../bridge/FamilyTreeController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FamilyTreeController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN20FamilyTreeControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto FamilyTreeController::qt_create_metaobjectdata<qt_meta_tag_ZN20FamilyTreeControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FamilyTreeController",
        "QML.Element",
        "auto",
        "QML.Singleton",
        "true",
        "treeChanged",
        "",
        "timelineChanged",
        "setYears",
        "QVariantMap",
        "Person*",
        "person",
        "birthYear",
        "deathYear",
        "loadTree",
        "root",
        "toggleCollapsed",
        "ancestryPath",
        "QVariantList",
        "registerRootPerson",
        "name",
        "gender",
        "registerNewFather",
        "child",
        "linkExistingFather",
        "father",
        "registerNewMother",
        "linkExistingMother",
        "mother",
        "registerNewSpouse",
        "linkExistingSpouse",
        "spouse",
        "registerNewChild",
        "parent",
        "linkExistingChild",
        "unlinkFather",
        "unlinkMother",
        "exportTree",
        "filePath",
        "importTree",
        "renamePerson",
        "newName",
        "markDeceased",
        "divorcePerson",
        "searchByName",
        "query",
        "searchById",
        "id",
        "trees",
        "PersonListModel*",
        "searchResults",
        "treeLayout",
        "TreeLayoutModel*",
        "totalPeople",
        "treeEdges",
        "activeRoot",
        "treeBounds",
        "QRectF",
        "timelineEnabled",
        "timelineYear"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'treeChanged'
        QtMocHelpers::SignalData<void()>(5, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'timelineChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'setYears'
        QtMocHelpers::MethodData<QVariantMap(Person *, int, int)>(8, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 }, { QMetaType::Int, 13 },
        }}),
        // Method 'loadTree'
        QtMocHelpers::MethodData<void(Person *)>(14, 6, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 15 },
        }}),
        // Method 'toggleCollapsed'
        QtMocHelpers::MethodData<void(Person *)>(16, 6, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'ancestryPath'
        QtMocHelpers::MethodData<QVariantList(Person *) const>(17, 6, QMC::AccessPublic, 0x80000000 | 18, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'registerRootPerson'
        QtMocHelpers::MethodData<QVariantMap(const QString &, const QString &)>(19, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { QMetaType::QString, 20 }, { QMetaType::QString, 21 },
        }}),
        // Method 'registerNewFather'
        QtMocHelpers::MethodData<QVariantMap(Person *, const QString &)>(22, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 23 }, { QMetaType::QString, 20 },
        }}),
        // Method 'linkExistingFather'
        QtMocHelpers::MethodData<QVariantMap(Person *, Person *)>(24, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 23 }, { 0x80000000 | 10, 25 },
        }}),
        // Method 'registerNewMother'
        QtMocHelpers::MethodData<QVariantMap(Person *, const QString &)>(26, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 23 }, { QMetaType::QString, 20 },
        }}),
        // Method 'linkExistingMother'
        QtMocHelpers::MethodData<QVariantMap(Person *, Person *)>(27, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 23 }, { 0x80000000 | 10, 28 },
        }}),
        // Method 'registerNewSpouse'
        QtMocHelpers::MethodData<QVariantMap(Person *, const QString &)>(29, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 20 },
        }}),
        // Method 'linkExistingSpouse'
        QtMocHelpers::MethodData<QVariantMap(Person *, Person *)>(30, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 11 }, { 0x80000000 | 10, 31 },
        }}),
        // Method 'registerNewChild'
        QtMocHelpers::MethodData<QVariantMap(Person *, const QString &, const QString &)>(32, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 33 }, { QMetaType::QString, 20 }, { QMetaType::QString, 21 },
        }}),
        // Method 'linkExistingChild'
        QtMocHelpers::MethodData<QVariantMap(Person *, Person *)>(34, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 33 }, { 0x80000000 | 10, 23 },
        }}),
        // Method 'unlinkFather'
        QtMocHelpers::MethodData<QVariantMap(Person *)>(35, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 23 },
        }}),
        // Method 'unlinkMother'
        QtMocHelpers::MethodData<QVariantMap(Person *)>(36, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 23 },
        }}),
        // Method 'exportTree'
        QtMocHelpers::MethodData<QVariantMap(Person *, const QString &)>(37, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 15 }, { QMetaType::QString, 38 },
        }}),
        // Method 'importTree'
        QtMocHelpers::MethodData<QVariantMap(const QString &)>(39, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { QMetaType::QString, 38 },
        }}),
        // Method 'renamePerson'
        QtMocHelpers::MethodData<QVariantMap(Person *, const QString &)>(40, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 41 },
        }}),
        // Method 'markDeceased'
        QtMocHelpers::MethodData<QVariantMap(Person *)>(42, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'divorcePerson'
        QtMocHelpers::MethodData<QVariantMap(Person *)>(43, 6, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'searchByName'
        QtMocHelpers::MethodData<int(const QString &)>(44, 6, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 45 },
        }}),
        // Method 'searchById'
        QtMocHelpers::MethodData<Person *(int)>(46, 6, QMC::AccessPublic, 0x80000000 | 10, {{
            { QMetaType::Int, 47 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'trees'
        QtMocHelpers::PropertyData<PersonListModel*>(48, 0x80000000 | 49, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'searchResults'
        QtMocHelpers::PropertyData<PersonListModel*>(50, 0x80000000 | 49, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'treeLayout'
        QtMocHelpers::PropertyData<TreeLayoutModel*>(51, 0x80000000 | 52, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'totalPeople'
        QtMocHelpers::PropertyData<int>(53, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'treeEdges'
        QtMocHelpers::PropertyData<QVariantList>(54, 0x80000000 | 18, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'activeRoot'
        QtMocHelpers::PropertyData<Person*>(55, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'treeBounds'
        QtMocHelpers::PropertyData<QRectF>(56, 0x80000000 | 57, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'timelineEnabled'
        QtMocHelpers::PropertyData<bool>(58, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'timelineYear'
        QtMocHelpers::PropertyData<int>(59, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<FamilyTreeController, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FamilyTreeController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20FamilyTreeControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20FamilyTreeControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20FamilyTreeControllerE_t>.metaTypes,
    nullptr
} };

void FamilyTreeController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FamilyTreeController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->treeChanged(); break;
        case 1: _t->timelineChanged(); break;
        case 2: { QVariantMap _r = _t->setYears((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->loadTree((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1]))); break;
        case 4: _t->toggleCollapsed((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1]))); break;
        case 5: { QVariantList _r = _t->ancestryPath((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantMap _r = _t->registerRootPerson((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantMap _r = _t->registerNewFather((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantMap _r = _t->linkExistingFather((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Person*>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantMap _r = _t->registerNewMother((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantMap _r = _t->linkExistingMother((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Person*>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantMap _r = _t->registerNewSpouse((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantMap _r = _t->linkExistingSpouse((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Person*>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 13: { QVariantMap _r = _t->registerNewChild((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantMap _r = _t->linkExistingChild((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Person*>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 15: { QVariantMap _r = _t->unlinkFather((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 16: { QVariantMap _r = _t->unlinkMother((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantMap _r = _t->exportTree((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantMap _r = _t->importTree((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 19: { QVariantMap _r = _t->renamePerson((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantMap _r = _t->markDeceased((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 21: { QVariantMap _r = _t->divorcePerson((*reinterpret_cast<std::add_pointer_t<Person*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->searchByName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 23: { Person* _r = _t->searchById((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<Person**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Person* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FamilyTreeController::*)()>(_a, &FamilyTreeController::treeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FamilyTreeController::*)()>(_a, &FamilyTreeController::timelineChanged, 1))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Person* >(); break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PersonListModel* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TreeLayoutModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<PersonListModel**>(_v) = _t->treesModel(); break;
        case 1: *reinterpret_cast<PersonListModel**>(_v) = _t->searchResultsModel(); break;
        case 2: *reinterpret_cast<TreeLayoutModel**>(_v) = _t->treeLayoutModel(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->totalPeople(); break;
        case 4: *reinterpret_cast<QVariantList*>(_v) = _t->treeEdges(); break;
        case 5: *reinterpret_cast<Person**>(_v) = _t->activeRoot(); break;
        case 6: *reinterpret_cast<QRectF*>(_v) = _t->treeBounds(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->timelineEnabled(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->timelineYear(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 7: _t->setTimelineEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 8: _t->setTimelineYear(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *FamilyTreeController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FamilyTreeController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20FamilyTreeControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FamilyTreeController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FamilyTreeController::treeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FamilyTreeController::timelineChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
