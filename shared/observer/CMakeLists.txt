# Define library
project(rtype_observer VERSION 1.0 LANGUAGES CXX)

#Include files
file(GLOB LIBOBSERVER_INCS "include/*.hpp")
source_group(Headers FILES ${LIBOBSERVER_INCS})

#Source files
file(GLOB LIBOBSERVER_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBOBSERVER_SRCS})

add_library(rtype_observer
    ${LIBOBSERVER_SRCS}
    ${LIBOBSERVER_INCS}
    )

target_include_directories(rtype_observer PUBLIC include)

set_property(TARGET rtype_observer PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_observer PROPERTY CXX_STANDARD_REQUIRED ON)
