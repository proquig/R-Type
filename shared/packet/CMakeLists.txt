# Define library
project(packet VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB LIBPACKET_INCS "include/*.hh")
source_group(Headers FILES ${LIBPACKET_INCS})

#Source files
file(GLOB LIBPACKET_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBPACKET_SRCS})

# Library
add_library(packet
        ${LIBPACKET_SRCS}
        ${LIBPACKET_INCS}
        )

# Link to game_element
target_link_libraries(packet PUBLIC rtype_game_element)

# Include directories
target_include_directories(packet PUBLIC include)

# C++ 11
set_property(TARGET packet PROPERTY CXX_STANDARD 11)
set_property(TARGET packet PROPERTY CXX_STANDARD_REQUIRED ON)