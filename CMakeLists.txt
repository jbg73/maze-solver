cmake_minimum_required(VERSION 3.12)

project(MazeSolver)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(maze-solver src/maze_creator.cpp)
target_link_libraries(maze-solver ${SDL2_LIBRARIES})