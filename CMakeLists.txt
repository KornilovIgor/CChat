cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME CChat)
project(${PROJECT_NAME})

file(GLOB CPPS "src/*.cpp")

find_package(OpenSSL REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${CPPS})

target_include_directories(CChat PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(CChat PRIVATE ${OPENSSL_LIBRARIES})