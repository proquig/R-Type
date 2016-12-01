include_directories(
	"../dlloader/include"
	"../dlloader/include/Win"
	)

add_executable(
	dlloader_test
	main.cpp)
	
target_link_libraries(dlloader_test dlloader)