/****************************************************************************
** Meta object code from reading C++ file 'Person.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../core/Person.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Person.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6PersonE_t {};
} // unnamed namespace

template <> constexpr inline auto Person::qt_create_metaobjectdata<qt_meta_tag_ZN6PersonE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Person",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "Person objects are created by FamilyForest, not from QML",
        "nameChanged",
        "",
        "statusChanged",
        "fatherChanged",
        "motherChanged",
        "spouseChanged",
        "childrenChanged",
        "birthYearChanged",
        "deathYearChanged",
        "id",
        "name",
        "gender",
        "Gender",
        "status",
        "LifeStatus",
        "father",
        "Person*",
        "mother",
        "spouse",
        "children",
        "QList<Person*>",
        "birthYear",
        "deathYear"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'nameChanged'
        QtMocHelpers::SignalData<void()>(7, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void()>(9, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fatherChanged'
        QtMocHelpers::SignalData<void()>(10, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'motherChanged'
        QtMocHelpers::SignalData<void()>(11, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'spouseChanged'
        QtMocHelpers::SignalData<void()>(12, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'childrenChanged'
        QtMocHelpers::SignalData<void()>(13, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'birthYearChanged'
        QtMocHelpers::SignalData<void()>(14, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'deathYearChanged'
        QtMocHelpers::SignalData<void()>(15, 8, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<int>(16, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'name'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'gender'
        QtMocHelpers::PropertyData<Gender>(18, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'status'
        QtMocHelpers::PropertyData<LifeStatus>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 1),
        // property 'father'
        QtMocHelpers::PropertyData<Person*>(22, 0x80000000 | 23, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
        // property 'mother'
        QtMocHelpers::PropertyData<Person*>(24, 0x80000000 | 23, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 3),
        // property 'spouse'
        QtMocHelpers::PropertyData<Person*>(25, 0x80000000 | 23, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'children'
        QtMocHelpers::PropertyData<QList<Person*>>(26, 0x80000000 | 27, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 5),
        // property 'birthYear'
        QtMocHelpers::PropertyData<int>(28, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'deathYear'
        QtMocHelpers::PropertyData<int>(29, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Person, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Person::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6PersonE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6PersonE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6PersonE_t>.metaTypes,
    nullptr
} };

void Person::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Person *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->nameChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->fatherChanged(); break;
        case 3: _t->motherChanged(); break;
        case 4: _t->spouseChanged(); break;
        case 5: _t->childrenChanged(); break;
        case 6: _t->birthYearChanged(); break;
        case 7: _t->deathYearChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::nameChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::statusChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::fatherChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::motherChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::spouseChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::childrenChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::birthYearChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Person::*)()>(_a, &Person::deathYearChanged, 7))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Person* >(); break;
        case 7:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<Person*> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->name(); break;
        case 2: *reinterpret_cast<Gender*>(_v) = _t->gender(); break;
        case 3: *reinterpret_cast<LifeStatus*>(_v) = _t->status(); break;
        case 4: *reinterpret_cast<Person**>(_v) = _t->father(); break;
        case 5: *reinterpret_cast<Person**>(_v) = _t->mother(); break;
        case 6: *reinterpret_cast<Person**>(_v) = _t->spouse(); break;
        case 7: *reinterpret_cast<QList<Person*>*>(_v) = _t->children(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->birthYear(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->deathYear(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setName(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setStatus(*reinterpret_cast<LifeStatus*>(_v)); break;
        case 8: _t->setBirthYear(*reinterpret_cast<int*>(_v)); break;
        case 9: _t->setDeathYear(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Person::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Person::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6PersonE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Person::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Person::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Person::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Person::fatherChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Person::motherChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Person::spouseChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Person::childrenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Person::birthYearChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Person::deathYearChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
