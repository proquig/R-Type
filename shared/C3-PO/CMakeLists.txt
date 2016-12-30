cmake_minimum_required(VERSION 3.2)

# Define library
project(C3PO VERSION 1.0 LANGUAGES CXX)

add_library(C3PO MODULE
        C3PO.cpp
        C3PO.hh
        )

target_include_directories(C3PO PUBLIC .)

if (MSVC)
    target_compile_options(C3PO PRIVATE -DRT_WIN)
else ()
    target_compile_options(C3PO PRIVATE -DRT_UNIX)
endif ()

target_link_libraries(C3PO PUBLIC rtype_game_element)

set_property(TARGET C3PO PROPERTY CXX_STANDARD 11)
set_property(TARGET C3PO PROPERTY CXX_STANDARD_REQUIRED ON)
