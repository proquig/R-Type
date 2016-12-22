# Define library
project(monster VERSION 1.0 LANGUAGES CXX)

add_library(monster
        Monster.cpp
        Monster.hh
        )

target_include_directories(monster PUBLIC . ../game_element/)

set_property(TARGET monster PROPERTY CXX_STANDARD 11)
set_property(TARGET monster PROPERTY CXX_STANDARD_REQUIRED ON)
