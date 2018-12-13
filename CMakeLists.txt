cmake_minimum_required(VERSION 3.13)
project(Code_C C)

set(CMAKE_C_STANDARD 11)

find_library(jasmine NAMES libjsmn_1_0_0.a PATHS ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Code_C main.c jsmn.h Supprimer.c Supprimer.h)

target_link_libraries(Code_C ${jasmine})