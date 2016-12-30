add_executable(C3PO_test
    main.cpp)

target_link_libraries(C3PO_test PRIVATE dlloader rtype_game_element)
target_include_directories(C3PO_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/C3-PO/)

add_test(
    NAME C3PO_test_job
    COMMAND C3PO_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Flags for different platforms
if (MSVC)
  target_compile_options(C3PO_test PRIVATE -DRT_WIN)
else ()
  target_compile_options(C3PO_test PRIVATE -DRT_UNIX)
endif ()

