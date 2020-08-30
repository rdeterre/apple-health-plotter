cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(apple-health-plotter)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME fmt
  GIT_TAG 7.0.3
  GITHUB_REPOSITORY fmtlib/fmt
  )

CPMAddPackage(
  NAME matplotplusplus
  GIT_TAG master
  GITHUB_REPOSITORY alandefreitas/matplotplusplus
  )


add_executable(apple-health-plotter src/main.cpp)
set_target_properties(apple-health-plotter PROPERTIES CXX_STANDARD 17)
target_link_libraries(apple-health-plotter fmt matplot)
