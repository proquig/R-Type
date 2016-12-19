# Define library
project(rtype_timer VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB LIBTIMER_INCS "include/*.hpp")
source_group(Headers FILES ${LIBTIMER_INCS})
file(GLOB LIBTIMER_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBTIMER_SRCS})

# Library
add_library(rtype_timer MODULE
    ${LIBTIMER_SRCS}
    ${LIBTIMER_INCS}
    )

# Include directories
target_include_directories(rtype_timer PUBLIC include)
target_include_directories(rtype_timer PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)

# Flags and libraries for different platforms
if (MSVC)
  target_compile_options(rtype_timer PRIVATE -DRT_WIN)
else ()
  target_compile_options(rtype_timer PRIVATE -DRT_UNIX)
endif ()

# Link libraries
target_link_libraries(rtype_timer PRIVATE dlloader rtype_observer)

# C++ 11
set_property(TARGET rtype_timer PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_timer PROPERTY CXX_STANDARD_REQUIRED ON)