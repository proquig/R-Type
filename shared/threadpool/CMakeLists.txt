cmake_minimum_required(VERSION 3.2)
 
# Files
file(GLOB LIBTHREADPOOL_INCS "include/*.hh")
source_group(Headers FILES ${LIBTHREADPOOL_INCS})
file(GLOB LIBTHREADPOOL_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBTHREADPOOL_SRCS})
 
# Platform files
if (UNIX)
  file(GLOB LIBTHREADPOOL_PLATFORM_INCS "include/Unix/*.hh")
  file(GLOB LIBTHREADPOOL_PLATFORM_SRCS "src/Unix/*.cpp")
  set(LIBTHREADPOOL_PLATFORM_INCLUDE include/Unix)
endif (UNIX)
if (MSVC)
  file(GLOB LIBTHREADPOOL_PLATFORM_INCS "include/Win/*.hh")
  file(GLOB LIBTHREADPOOL_PLATFORM_SRCS "src/Win/*.cpp")
  set(LIBTHREADPOOL_PLATFORM_INCLUDE include/Win)
endif (MSVC)
 
# Library
add_library(threadpool MODULE
    ${LIBTHREADPOOL_SRCS}
    ${LIBTHREADPOOL_INCS}
    ${LIBTHREADPOOL_PLATFORM_INCS}
    ${LIBTHREADPOOL_PLATFORM_SRCS}
    )
 
# Include directories
target_include_directories(threadpool PUBLIC include)
target_include_directories(threadpool PRIVATE ${LIBTHREADPOOL_PLATFORM_INCLUDE})
 
# Flags for different platforms
if (MSVC)
  target_compile_options(threadpool PRIVATE -DRT_WIN)
else ()
  target_compile_options(threadpool PRIVATE -DRT_UNIX)
endif ()

# Unix pthread
if (UNIX)
  if (Threads_FOUND)
    target_link_libraries(threadpool PUBLIC Threads::Threads)
  endif ()
endif()
 
# C++ 11
set_property(TARGET threadpool PROPERTY CXX_STANDARD 11)
set_property(TARGET threadpool PROPERTY CXX_STANDARD_REQUIRED ON)