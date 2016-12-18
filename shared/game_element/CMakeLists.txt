# Define library
project(rtype_game_element VERSION 1.0 LANGUAGES CXX)

add_library(rtype_game_element
    GameElement.cpp
    GameElement.hpp
	IElement.hh
	AElement.hh
	AElement.cpp
    )

target_include_directories(rtype_game_element PUBLIC .)

set_property(TARGET rtype_game_element PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_game_element PROPERTY CXX_STANDARD_REQUIRED ON)
