cmake_minimum_required(VERSION 3.2)

# Define library
project(Boss VERSION 1.0 LANGUAGES CXX)

add_library(Boss MODULE
        Boss.cpp
        Boss.hh
        )

target_include_directories(Boss PUBLIC .)

if (MSVC)
    target_compile_options(Boss PRIVATE -DRT_WIN)
else ()
    target_compile_options(Boss PRIVATE -DRT_UNIX)
endif ()

target_link_libraries(Boss PUBLIC rtype_game_element)

set_property(TARGET Boss PROPERTY CXX_STANDARD 11)
set_property(TARGET Boss PROPERTY CXX_STANDARD_REQUIRED ON)
