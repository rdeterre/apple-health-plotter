cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(apple-health-plotter)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(date REQUIRED)
find_package(pugixml REQUIRED)
find_package(fmt REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Charts)

add_executable(apple-health-plotter WIN32 src/main.cpp src/applehealthplotter.cpp)
set_target_properties(apple-health-plotter PROPERTIES CXX_STANDARD 17)
target_link_libraries(apple-health-plotter 
  date::date fmt::fmt Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts pugixml)
set_property(TARGET apple-health-plotter PROPERTY
             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")