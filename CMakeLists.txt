cmake_minimum_required(VERSION 3.5)

project(mytest LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

enable_testing(true)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(mytest
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ModeSelect.ui
    ModeSelect.h
    ModeSelect.cpp
    HomeMenu.h
    HomeMenu.cpp
    HomeMenu.ui
    LoadOptions.cpp
    LoadOptions.h
    LoadOptions.ui
    SingleMode.ui
    SingleMode.h
    SingleMode.cpp
    Cell.h
    Cell.cpp
    randomgenerator.h randomgenerator.cpp
    MapGenerator.h MapGenerator.cpp
    Border.h Border.cpp
    LinkLine.h
    Position.h
    background.qrc
    DuoMode.h
    DuoMode.cpp
    DuoMode.ui
    selectfunctiontest.cpp selectfunctiontest.h
)
add_test(NAME mytest COMMAND mytest)

target_link_libraries(mytest PRIVATE Qt::Test)
target_link_libraries(mytest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

##-------------------test   and   QLink   line---------------------------------------
#project(QLink VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

#set(PROJECT_SOURCES
#        main.cpp
#        mainwindow.cpp
#        mainwindow.h
#        mainwindow.ui
#        ${TS_FILES}
#)

#qt_add_executable(QLink
#    MANUAL_FINALIZATION
#    ${PROJECT_SOURCES}
#    ModeSelect.ui
#    ModeSelect.h
#    ModeSelect.cpp
#    HomeMenu.h
#    HomeMenu.cpp
#    HomeMenu.ui
#    LoadOptions.cpp
#    LoadOptions.h
#    LoadOptions.ui
#    SingleMode.ui
#    SingleMode.h
#    SingleMode.cpp
#    Cell.h
#    Cell.cpp
#    randomgenerator.h randomgenerator.cpp
#    MapGenerator.h MapGenerator.cpp
#    Border.h Border.cpp
#    LinkLine.h
#    Position.h
#    background.qrc
#    DuoMode.h
#    DuoMode.cpp
#    DuoMode.ui
#)
#target_link_libraries(QLink PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

