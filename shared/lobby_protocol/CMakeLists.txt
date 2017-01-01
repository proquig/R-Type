# Define library
project(rtype_lobby_protocol VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB LIBRTYPE_LOBBY_PROTOCOL_INCS "include/*.hpp")
source_group(Headers FILES ${LIBRTYPE_LOBBY_PROTOCOL_INCS})

#Source files
file(GLOB LIBRTYPE_LOBBY_PROTOCOL_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBRTYPE_LOBBY_PROTOCOL_SRCS})

# Library
add_library(rtype_lobby_protocol
        ${LIBRTYPE_LOBBY_PROTOCOL_SRCS}
        ${LIBRTYPE_LOBBY_PROTOCOL_INCS}
        )

# Include directories
target_include_directories(rtype_lobby_protocol PUBLIC include)

# C++ 11
set_property(TARGET rtype_lobby_protocol PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_lobby_protocol PROPERTY CXX_STANDARD_REQUIRED ON)