add_executable(network_test
    Server.hpp
    Server.cpp
    main.cpp)

target_link_libraries(network_test PRIVATE dlloader rtype_observer)
target_include_directories(network_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)
target_include_directories(network_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/network/include)

add_test(
    NAME network_test_job
    COMMAND network_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Flags for different platforms
if (MSVC)
  target_compile_options(network_test PRIVATE -DRT_WIN)
else ()
  target_compile_options(network_test PRIVATE -DRT_UNIX)
endif ()

if (UNIX)
  if (Threads_FOUND)
    target_link_libraries(network_test PUBLIC Threads::Threads)
  endif ()
endif()
