# Define library
project(rtype_game_element VERSION 1.0 LANGUAGES CXX)

add_library(rtype_game_element
    GameElement.cpp
    GameElement.hpp
	IElement.hh
	AElement.hh
	AElement.cpp
	Decor.hh
	Decor.cpp
	Player.hh
	Player.cpp
	Shot.cpp
	Shot.hh
	ElementFactory.hh
	ElementFactory.cpp
	Rectangle.cpp
	Rectangle.hh
	TripleShot.hh
	TripleShot.cpp
        ../monster/Monster.cpp
        ../monster/Monster.hh
		../Bildo/Bildo.cpp
		../Bildo/Bildo.hh
		)

target_include_directories(rtype_game_element PUBLIC . ../monster ../Bildo)

target_link_libraries(rtype_game_element PUBLIC rtype_common)

set_property(TARGET rtype_game_element PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_game_element PROPERTY CXX_STANDARD_REQUIRED ON)
