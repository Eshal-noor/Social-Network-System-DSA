cmake_minimum_required(VERSION 3.16)
project(SocialNetwork VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui OpenGL)

set(SOURCES
    main.cpp
    mainwindow.cpp
    profilearray.cpp
    doublylist.cpp
    chatstack.cpp
    newsfeedqueue.cpp
    bst.cpp
    graphlist.cpp
)

set(HEADERS
    mainwindow.h
    profilearray.h
    doublylist.h
    chatstack.h
    newsfeedqueue.h
    bst.h
    graphlist.h
)

qt_add_executable(SocialNetwork
    ${SOURCES}
    ${HEADERS}
    resources.qrc
)

target_link_libraries(SocialNetwork PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::OpenGL
)

if(APPLE)
    set_target_properties(SocialNetwork PROPERTIES MACOSX_BUNDLE TRUE)
    target_link_options(SocialNetwork PRIVATE -Wl,-w,-undefined,dynamic_lookup)
endif()
