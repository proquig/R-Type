add_executable(dlloader_test
    main.cpp)
	
target_link_libraries(dlloader_test PRIVATE dlloader)
target_include_directories(dlloader_test PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)

# Flags for different platforms
if (MSVC)
  target_compile_options(dlloader_test PRIVATE -DRT_WIN)
else ()
  target_compile_options(dlloader_test PRIVATE -DRT_UNIX)
endif ()

if (UNIX)
  if (Threads_FOUND)
    target_link_libraries(dlloader_test PUBLIC Threads::Threads)
  endif ()
endif()
