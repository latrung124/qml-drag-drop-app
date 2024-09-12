cmake_minimum_required(VERSION 3.14)

project(test_app LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Qml Quick Core5Compat)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Qml Quick Core5Compat)

add_executable(test_app
  main.cpp
  # resources.qrc
)

qt6_add_qml_module(test_app
    URI HMI
    VERSION 1.0
    QML_FILES
    main.qml
    AssignmentItemRow.qml
    AssignmentMode.qml
    SOURCES backend_component/ImageProvider.h
    SOURCES backend_component/AssignmentItem.h
    SOURCES backend_component/AssignmentItemList.h

    SOURCES backend_component/AssignmentItem.cpp
    SOURCES backend_component/AssignmentItemList.cpp
    SOURCES backend_component/ImageProvider.cpp
)

target_link_libraries(test_app  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Quick
    Qt6::Core5Compat)

include(GNUInstallDirs)
install(TARGETS test_app
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
