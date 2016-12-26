# Define library
project(rtype_common VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB LIBRTYPE_COMMON_INCS "./*.hpp")
source_group(Headers FILES ${LIBRTYPE_COMMON_INCS})

# Library
add_library(rtype_common INTERFACE)

# Specify header files for IDE
target_sources(rtype_common
    INTERFACE ${LIBRTYPE_COMMON_INCS})

# Include directories
target_include_directories(rtype_common INTERFACE .)
