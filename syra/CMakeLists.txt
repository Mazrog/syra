file( GLOB SYRA_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        include/syra/*.hpp include/syra/*/*.hpp
        src/*.cpp src/*/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SYRA_FILES})