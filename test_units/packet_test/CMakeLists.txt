add_executable(packet_test
    main.cpp)

target_link_libraries(packet_test PRIVATE packet)

target_include_directories(packet_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/packet/include)

add_test(
    NAME packet_test_job
    COMMAND packet_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )