cmake_minimum_required(VERSION 3.21)
project(Client)

add_executable(${PROJECT_NAME} main.cpp Session.h Menu.h Global.h Source/Menu.cpp Source/Session.cpp)

set(CMAKE_CXX_STANDARD 23)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS thread system REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads fort ${Boost_LIBRARIES})
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})