cmake_minimum_required(VERSION 3.21)

project(PhoenixDesktop
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
)

find_package(LayerShellQt REQUIRED)

qt_standard_project_setup()

qt_add_executable(PhoenixDesktop
    app/src/main.cpp
    app/src/Application.cpp
    app/src/Application.hpp

    app/src/DesktopManager.cpp
    app/src/DesktopManager.hpp
    )

set_source_files_properties(
    qml/Themes/PhoenixTheme.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(PhoenixDesktop
    URI Phoenix
    VERSION 1.0

    QML_FILES
        app/Main.qml
        app/Shell.qml
        
        qml/Shell/Desktop.qml
        qml/Shell/DesktopIcon.qml
        qml/Shell/TopBar.qml
        qml/Shell/Island.qml

        qml/Themes/PhoenixTheme.qml
)

target_link_libraries(PhoenixDesktop
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        LayerShellQt::Interface
)