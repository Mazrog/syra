cmake_minimum_required(VERSION 3.5)

project( syra )

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)


include_directories(PRIVATE syra/include extern)
add_subdirectory(syra)

file(GLOB SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        src/*.cpp
        src/*.hpp
)

add_executable(
        client
        sample/client.cpp

        ${SRC_FILES}
)

add_executable(
        server
        sample/server.cpp

        ${SRC_FILES}
)

add_executable(
        ros_client
        tests/main_tests.cpp

        ${SRC_FILES}
)

target_link_libraries(
        client
        ${PROJECT_NAME}
        pthread
)

target_link_libraries(
        server
        ${PROJECT_NAME}
        pthread
)

target_link_libraries(
        ros_client
        ${PROJECT_NAME}
)