add_executable(bildo_test
    main.cpp)

target_link_libraries(bildo_test PRIVATE dlloader rtype_game_element)
target_include_directories(bildo_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/Bildo/)

add_test(
    NAME bildo_test_job
    COMMAND bildo_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Flags for different platforms
if (MSVC)
  target_compile_options(bildo_test PRIVATE -DRT_WIN)
else ()
  target_compile_options(bildo_test PRIVATE -DRT_UNIX)
endif ()

