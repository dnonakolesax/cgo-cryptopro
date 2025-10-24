cmake_minimum_required(VERSION 3.0.0)
project(cryptopro_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CRYPTOPRO_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CRYPTOPRO_LIBRARIES} GTest::GTest GTest::Main)
