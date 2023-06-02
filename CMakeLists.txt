cmake_minimum_required(VERSION 3.12)

project(MazeSolver)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)
include_directories(common)

add_executable(maze-solver src/cell.cpp src/maze_generator.cpp)
target_link_libraries(maze-solver ${SDL2_LIBRARIES})