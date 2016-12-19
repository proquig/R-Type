project(rtype_client VERSION 1.0 LANGUAGES CXX)

#Include files
file(GLOB RTYPE_CLIENT_INCS "include/*.hh")
source_group(Headers FILES ${RTYPE_CLIENT_INCS})

#Source files
file(GLOB RTYPE_CLIENT_SRCS "src/*.cpp")
source_group(Sources FILES ${RTYPE_CLIENT_SRCS})

add_executable(rtype_client
    ${RTYPE_CLIENT_SRCS}
    ${RTYPE_CLIENT_INCS}
    )

target_link_libraries(rtype_client PUBLIC dlloader rtype_observer rtype_game_element)

if (SFML_EXTERNAL)
  target_link_libraries(rtype_client PUBLIC sfml-system sfml-window sfml-graphics sfml-audio)
else()
  target_link_libraries(rtype_client PUBLIC ${SFML_LIBRARIES})
endif()

if (UNIX)
  if (Threads_FOUND)
    target_link_libraries(rtype_client PUBLIC Threads::Threads)
  endif ()
endif()

target_include_directories(rtype_client PUBLIC include)
target_include_directories(rtype_client PRIVATE ${SFML_INCLUDE_DIR})
target_include_directories(rtype_client PRIVATE ${CMAKE_SOURCE_DIR}/shared/packet/include)
target_include_directories(rtype_client PRIVATE ${CMAKE_SOURCE_DIR}/shared/threadpool/include)
target_include_directories(rtype_client PRIVATE ${CMAKE_SOURCE_DIR}/shared/network/include)

target_link_libraries(rtype_client PRIVATE packet)

set_property(TARGET rtype_client PROPERTY CXX_STANDARD 11)
set_property(TARGET rtype_client PROPERTY CXX_STANDARD_REQUIRED ON)
