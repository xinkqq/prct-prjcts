cmake_minimum_required(VERSION 3.20)
project(SFML)

set(CMAKE_CXX_STANDARD 23)
add_executable(SFML main.cpp)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(SFML sfml-graphics sfml-audio)