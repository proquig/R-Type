add_executable(lobby_test
    main.cpp)

target_link_libraries(lobby_test PUBLIC rtype_lobby_protocol)

add_test(
    NAME lobby_test_job
    COMMAND lobby_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )