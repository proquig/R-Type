add_executable(monster_test
    main.cpp)

target_link_libraries(monster_test PRIVATE dlloader rtype_game_element rtype_observer rtype_gamehandler)
target_include_directories(monster_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/game_element/)

add_test(
    NAME monster_test_job
    COMMAND monster_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Flags for different platforms
if (MSVC)
  target_compile_options(monster_test PRIVATE -DRT_WIN)
else ()
  target_compile_options(monster_test PRIVATE -DRT_UNIX)
endif ()

