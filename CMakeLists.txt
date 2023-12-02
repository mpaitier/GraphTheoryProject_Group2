cmake_minimum_required(VERSION 3.18)
project(GraphTheory)

set(CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE Projet src/*.cpp src/*.h)

add_executable(GraphTheoryProject_Group2 ${Projet})
