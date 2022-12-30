cmake_minimum_required(VERSION 3.21)
project(square)

set(CMAKE_CXX_STANDARD 20)

add_executable(square main.cpp
        structures/playing_field/playing_field.h
        structures/playing_field/playing_field.cpp
        structures/cubes/cubes.h structures/cubes/cubes.cpp
        structures/color/color.h structures/player/player.h
        structures/player/player.cpp)
