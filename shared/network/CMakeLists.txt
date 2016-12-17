# Define library
project(rtype_network VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB LIBNETWORK_INCS "include/*.hpp")
source_group(Headers FILES ${LIBNETWORK_INCS})
file(GLOB LIBNETWORK_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBNETWORK_SRCS})

# Platform files
if (UNIX)
  file(GLOB LIBNETWORK_PLATFORM_INCS "include/Unix/*.hpp")
  file(GLOB LIBNETWORK_PLATFORM_SRCS "src/Unix/*.cpp")
  set(LIBNETWORK_PLATFORM_INCLUDE include/Unix)
endif (UNIX)
if (MSVC)
  file(GLOB LIBNETWORK_PLATFORM_INCS "include/Win/*.hpp")
  file(GLOB LIBNETWORK_PLATFORM_SRCS "src/Win/*.cpp")
  set(LIBNETWORK_PLATFORM_INCLUDE include/Win)
endif (MSVC)

# Library
add_library(rtype_network MODULE
    ${LIBNETWORK_SRCS}
    ${LIBNETWORK_INCS}
    ${LIBNETWORK_PLATFORM_INCS}
    ${LIBNETWORK_PLATFORM_SRCS}
    )

# Include directories
target_include_directories(rtype_network PUBLIC include)
target_include_directories(rtype_network PRIVATE ${LIBNETWORK_PLATFORM_INCLUDE})
target_include_directories(rtype_network PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)

# Flags and libraries for different platforms
if (MSVC)
  target_compile_options(rtype_network PRIVATE -DRT_WIN)
  target_link_libraries(rtype_network PRIVATE wsock32 ws2_32 dlloader rtype_observer)
else ()
  target_compile_options(rtype_network PRIVATE -DRT_UNIX)
  target_link_libraries(rtype_network PRIVATE dlloader rtype_observer)
endif ()

# C++ 11
set_property(TARGET rtype_network PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_network PROPERTY CXX_STANDARD_REQUIRED ON)