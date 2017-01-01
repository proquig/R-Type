cmake_minimum_required(VERSION 3.2)

# Define library
project(bildo VERSION 1.0 LANGUAGES CXX)

add_library(bildo MODULE
        Bildo.cpp
        Bildo.hh
        )

target_include_directories(bildo PUBLIC .)

if (MSVC)
    target_compile_options(bildo PRIVATE -DRT_WIN)
else ()
    target_compile_options(bildo PRIVATE -DRT_UNIX)
endif ()

target_link_libraries(bildo PUBLIC rtype_game_element)

set_property(TARGET bildo PROPERTY CXX_STANDARD 11)
set_property(TARGET bildo PROPERTY CXX_STANDARD_REQUIRED ON)
