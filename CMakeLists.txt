cmake_minimum_required(VERSION 3.15)

project(map_qml
        VERSION 1.0.0
        DESCRIPTION "Log saver"
        LANGUAGES CXX
)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)
endif ()

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
        Core
        Widgets
        Positioning
        Location
)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        src/c++
)

target_sources(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/line_f_list.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/line_f_list.h
        ${CMAKE_CURRENT_SOURCE_DIR}/logic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/restricted_area.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/restricted_area.h
        ${CMAKE_CURRENT_SOURCE_DIR}/restricted_area_list.h
        ${CMAKE_CURRENT_SOURCE_DIR}/restricted_area_list.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/way_point.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/way_point.h
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Positioning
        Qt${QT_VERSION_MAJOR}::Location
)

message("${PROJECT_NAME} version ${PROJECT_VERSION} compiled successfully")

#unset(UNITTEST CACHE)
