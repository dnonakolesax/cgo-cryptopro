cmake_minimum_required(VERSION 3.0.0)
project(cryptopro
    LANGUAGES C)

set(THIS_LIB_NAME CRYPTOPRO)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fPIC -shared")

file (GLOB SOURCES src/*.c)
add_library (${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC /opt/cprocsp/include)
target_include_directories(${PROJECT_NAME} PUBLIC /opt/cprocsp/include/cpcsp)
target_include_directories(${PROJECT_NAME} PUBLIC /opt/cprocsp/include/pki)

target_link_libraries(${PROJECT_NAME} /opt/cprocsp/lib/amd64/libcapi10.so)
target_link_libraries(${PROJECT_NAME} /opt/cprocsp/lib/amd64/libcapi20.so)
target_link_libraries(${PROJECT_NAME} /opt/cprocsp/lib/amd64/libcsp.so)
target_link_libraries(${PROJECT_NAME} /opt/cprocsp/lib/amd64/librdrsup.so)

set(CRYPTOPRO_LIBRARIES ${PROJECT_NAME})
set(CRYPTOPRO_INCLUDE_DIRS ${INCLUDE_DIRS})

if (${TEST})
    add_subdirectory(tests)
endif ()
