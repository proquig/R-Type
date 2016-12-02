# Define library
project(rtype_dlloader VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB DLLOADER_INCS "include/*.hh")
source_group(Headers FILES ${DLLOADER_INCS})
file(GLOB DLLOADER_SRCS "src/*.cpp")
source_group(Sources FILES ${DLLOADER_SRCS})
 
# Platform files
if (UNIX)
  file(GLOB DLLOADER_PLATFORM_INCS "include/Unix/*.hh")
  file(GLOB DLLOADER_PLATFORM_SRCS "src/Unix/*.cpp")
  set(DLLOADER_PLATFORM_INCLUDE include/Unix)
endif (UNIX)
if (MSVC)
  file(GLOB DLLOADER_PLATFORM_INCS "include/Win/*.hh")
  file(GLOB DLLOADER_PLATFORM_SRCS "src/Win/*.cpp")
  set(DLLOADER_PLATFORM_INCLUDE include/Win)
endif (MSVC)
 
# Library
add_library(dlloader
	STATIC
    ${DLLOADER_SRCS}
    ${DLLOADER_INCS}
    ${DLLOADER_PLATFORM_INCS}
    ${DLLOADER_PLATFORM_SRCS}
    )
 
# Include directories
target_include_directories(dlloader PUBLIC include)
target_include_directories(dlloader PRIVATE ${DLLOADER_PLATFORM_INCLUDE})
 
# Flags for different platforms
if (MSVC)
  target_compile_options(dlloader PRIVATE -DRT_WIN)
else ()
  target_compile_options(dlloader PRIVATE -DRT_UNIX)
  target_link_libraries(dlloader PUBLIC ${CMAKE_DL_LIBS})
endif ()
 
# C++ 11
set_property(TARGET dlloader PROPERTY CXX_STANDARD 11)
set_property(TARGET dlloader PROPERTY CXX_STANDARD_REQUIRED ON)