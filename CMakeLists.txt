cmake_minimum_required(VERSION 3.4)

enable_language(CXX)

project(R-Type)

find_package(SFML 2.4 QUIET COMPONENTS system window graphics audio)
if (NOT SFML_FOUND)
  find_package(Git REQUIRED)
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" submodule update --init -- SFML
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	)
  add_subdirectory(SFML)
endif()

add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(test_units)
