# Define library
cmake_minimum_required(VERSION 3.6)

project(rtype_gamehandler VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB GAMEHANDLER_INCS "include/*.hh")
source_group(Headers FILES ${GAMEHANDLER_INCS})
file(GLOB GAMEHANDLER_SRCS "src/*.cpp")
source_group(Sources FILES ${GAMEHANDLER_SRCS})

add_executable(rtype_gamehandler
				${GAMEHANDLER_SRCS}
				${GAMEHANDLER_INCS})
  
# Include directories
target_include_directories(rtype_gamehandler PUBLIC include)
target_include_directories(rtype_gamehandler PRIVATE ${GAMEHANDLER_PLATFORM_INCLUDE})
target_link_libraries(rtype_gamehandler PUBLIC rtype_game_element)
 
# Flags for different platforms
if (MSVC)
  target_compile_options(rtype_gamehandler PRIVATE -DRT_WIN)
else ()
  target_compile_options(rtype_gamehandler PRIVATE -DRT_UNIX)
  target_link_libraries(rtype_gamehandler PUBLIC ${CMAKE_DL_LIBS})
endif ()
 
# C++ 11
set_property(TARGET rtype_gamehandler PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_gamehandler PROPERTY CXX_STANDARD_REQUIRED ON)