/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<FamilyTreeController.h>)
#  include <FamilyTreeController.h>
#endif
#if __has_include(<Person.h>)
#  include <Person.h>
#endif
#if __has_include(<PersonListModel.h>)
#  include <PersonListModel.h>
#endif
#if __has_include(<TreeLayoutModel.h>)
#  include <TreeLayoutModel.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_FamilyTreeQt()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<FamilyTreeController>("FamilyTreeQt", 1);
    qmlRegisterTypesAndRevisions<Person>("FamilyTreeQt", 1);
    qmlRegisterTypesAndRevisions<PersonListModel>("FamilyTreeQt", 1);
    QMetaType::fromType<QAbstractItemModel *>().id();
    qmlRegisterEnum<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");
    qmlRegisterEnum<QAbstractItemModel::CheckIndexOption>("QAbstractItemModel::CheckIndexOption");
    QMetaType::fromType<QAbstractListModel *>().id();
    qmlRegisterTypesAndRevisions<TreeLayoutModel>("FamilyTreeQt", 1);
    QT_WARNING_POP
    qmlRegisterModule("FamilyTreeQt", 1, 0);
}

static const QQmlModuleRegistration familyTreeQtRegistration("FamilyTreeQt", qml_register_types_FamilyTreeQt);
