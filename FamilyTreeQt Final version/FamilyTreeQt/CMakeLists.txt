cmake_minimum_required(VERSION 3.21)

project(FamilyTreeQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.4)

set_source_files_properties(qml/Theme.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)
set_source_files_properties(qml/AppSettings.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)
set_source_files_properties(qml/Toast.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_executable(FamilyTreeApp
    main.cpp
    core/Person.h
    core/Person.cpp
    core/FamilyForest.h
    core/FamilyForest.cpp
    core/Relationships.h
    core/TreeLayoutEngine.h
    core/XmlExporter.h
    core/XmlImporter.h
    core/Types.h
    bridge/PersonListModel.h
    bridge/PersonListModel.cpp
    bridge/TreeLayoutModel.h
    bridge/TreeLayoutModel.cpp
    bridge/FamilyTreeController.h
    bridge/FamilyTreeController.cpp
)

qt_add_qml_module(FamilyTreeApp
    URI FamilyTreeQt
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/Theme.qml
        qml/AppSettings.qml
        qml/Toast.qml
        qml/ToastHost.qml
        qml/ConfirmDialog.qml
        qml/PersonPicker.qml
        qml/SplashScreen.qml
        qml/Dashboard.qml
        qml/TreeView.qml
        qml/PersonCard.qml
        qml/InfoPanel.qml
        qml/NavButton.qml
    SOURCES
        core/Person.h
        core/Person.cpp
        bridge/PersonListModel.h
        bridge/PersonListModel.cpp
        bridge/TreeLayoutModel.h
        bridge/TreeLayoutModel.cpp
        bridge/FamilyTreeController.h
        bridge/FamilyTreeController.cpp
)

target_link_libraries(FamilyTreeApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

target_include_directories(FamilyTreeApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/bridge
)
