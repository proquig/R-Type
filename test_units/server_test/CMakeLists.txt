add_test(
    NAME server_test_job
    COMMAND rtype_server 5454 4296 5
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)