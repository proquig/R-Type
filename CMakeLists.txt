cmake_minimum_required(VERSION 3.4)

enable_language(CXX)

project(R-Type)

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
  set_target_properties(sfml-main PROPERTIES
      EXCLUDE_FROM_ALL 1
      EXCLUDE_FROM_DEFAULT_BUILD 1
      )
  set_target_properties(sfml-network PROPERTIES
      EXCLUDE_FROM_ALL 1
      EXCLUDE_FROM_DEFAULT_BUILD 1
      )
  macro(install)
    _install(${ARGV})
  endmacro(install)
  set(SFML_EXTERNAL True)
  set(SFML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SFML/include)
endif ()

# CMake output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${PROJECT_BINARY_DIR}/bin" CACHE PATH "" FORCE)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${PROJECT_BINARY_DIR}/bin" CACHE PATH "" FORCE)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${PROJECT_BINARY_DIR}/lib" CACHE PATH "" FORCE)
endforeach ()

# Flag for windows
if (MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif ()

add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(test_units)
