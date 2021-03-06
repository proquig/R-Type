cmake_minimum_required(VERSION 3.4)

enable_language(CXX)
enable_testing()

project(R-Type)

# Set PIC ON
set(CMAKE_POSITION_INDEPENDENT_CODE True)

# CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Set files for copy
file(
  GLOB rtype_files
if (MSVC)
  ${PROJECT_SOURCE_DIR}/SFML/extlibs/bin/x86/openal32.dll
endif()
)

# Add target for copying files
add_custom_target(rtype_install)
foreach(FileToCopy ${rtype_files})
  add_custom_command(TARGET rtype_install PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E
                         copy ${FileToCopy} ${PROJECT_BINARY_DIR}/bin)
endforeach()

# SFML detection
set(SFML_EXTERNAL False)
find_package(SFML 2.4 QUIET COMPONENTS system window graphics audio)
if (NOT SFML_FOUND)
  find_package(Git REQUIRED)
  execute_process(
      COMMAND "${GIT_EXECUTABLE}" submodule update --init -- SFML
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
  macro(install)
  endmacro()
  add_subdirectory(SFML)
  set_target_properties(sfml-network PROPERTIES
      EXCLUDE_FROM_ALL 1
      EXCLUDE_FROM_DEFAULT_BUILD 1
      )
  if (MSVC)
    set_target_properties(sfml-main PROPERTIES
        EXCLUDE_FROM_ALL 1
        EXCLUDE_FROM_DEFAULT_BUILD 1
        )
  endif()
  macro(install)
    _install(${ARGV})
  endmacro(install)
  set(SFML_EXTERNAL True)
  set(SFML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SFML/include)
endif ()

# CMake output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${PROJECT_BINARY_DIR}/bin" CACHE PATH "" FORCE)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${PROJECT_BINARY_DIR}/bin" CACHE PATH "" FORCE)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${PROJECT_BINARY_DIR}/bin" CACHE PATH "" FORCE)
endforeach ()

# Flag for windows
if (MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif ()

# Unix PThread
if (UNIX)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
endif()

add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(test_units)
