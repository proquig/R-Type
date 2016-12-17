# Define library
project(rtype_server_core VERSION 1.0 LANGUAGES CXX)

# Files
file(GLOB LIBRTYPE_SERVER_CORE_INCS "include/*.hpp")
source_group(Headers FILES ${LIBRTYPE_SERVER_CORE_INCS})
file(GLOB LIBRTYPE_SERVER_CORE_SRCS "src/*.cpp")
source_group(Sources FILES ${LIBRTYPE_SERVER_CORE_SRCS})

# Executable
add_executable(rtype_server
    ${LIBRTYPE_SERVER_CORE_SRCS}
    ${LIBRTYPE_SERVER_CORE_INCS}
    )

# Include directories
target_include_directories(rtype_server PUBLIC include)
target_include_directories(rtype_server PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)
target_include_directories(rtype_server PRIVATE ${CMAKE_SOURCE_DIR}/shared/network/include)

# Flags and libraries for different platforms
if (MSVC)
  target_compile_options(rtype_server PRIVATE -DRT_WIN)
  #target_link_libraries(rtype_server PRIVATE wsock32 ws2_32)
else ()
  target_compile_options(rtype_server PRIVATE -DRT_UNIX)
endif ()

target_link_libraries(rtype_server PRIVATE dlloader rtype_observer)

if (UNIX)
  if (Threads_FOUND)
    target_link_libraries(rtype_server PUBLIC Threads::Threads)
  endif ()
endif()

# C++ 11
set_property(TARGET rtype_server PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_server PROPERTY CXX_STANDARD_REQUIRED ON)