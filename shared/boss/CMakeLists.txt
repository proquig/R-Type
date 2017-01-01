cmake_minimum_required(VERSION 3.2)

# Define library
project(boss VERSION 1.0 LANGUAGES CXX)

add_library(boss MODULE
        Boss.cpp
        Boss.hh
        )

target_include_directories(boss PUBLIC .)

if (MSVC)
    target_compile_options(boss PRIVATE -DRT_WIN)
else ()
    target_compile_options(boss PRIVATE -DRT_UNIX)
endif ()

target_link_libraries(boss PUBLIC rtype_game_element)

set_property(TARGET boss PROPERTY CXX_STANDARD 11)
set_property(TARGET boss PROPERTY CXX_STANDARD_REQUIRED ON)
