add_executable(gamehandler_test
    main.cpp)

target_link_libraries(gamehandler_test PRIVATE dlloader rtype_game_element rtype_observer rtype_gamehandler)
target_include_directories(gamehandler_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)
target_include_directories(gamehandler_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/network/include)

add_test(
    NAME gamehandler_test_job
    COMMAND gamehandler_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Flags for different platforms
if (MSVC)
  target_compile_options(gamehandler_test PRIVATE -DRT_WIN)
else ()
  target_compile_options(gamehandler_test PRIVATE -DRT_UNIX)
endif ()

if (UNIX)
  if (Threads_FOUND)
    target_link_libraries(gamehandler_test PUBLIC Threads::Threads)
  endif ()
endif()
