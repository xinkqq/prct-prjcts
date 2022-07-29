cmake_minimum_required(VERSION 3.21)
project(Server)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_subdirectory(../lib/libfort [binary_dir])


add_executable(${PROJECT_NAME} main.cpp ClientSession.h Global.h DataBase.h Client.h Server.h Order.h Book.h Person.h Author.h Source/Server.cpp Source/Person.cpp Source/Client.cpp Source/Book.cpp Source/Author.cpp Source/Order.cpp Source/SessionLib.cpp Source/Buffs.cpp Source/DataBase.cpp Buffs.h Sha256.h Source/Sha256.cpp)

set(CMAKE_CXX_STANDARD 23)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS thread system REQUIRED)

include_directories (${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads fort ${Boost_LIBRARIES})
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

target_include_directories(${PROJECT_NAME} PUBLIC /home/xink/Загрузки/connectorSQL/include/jdbc
        /home/xink/Загрузки/connectorSQL/include/
        /home/xink/Загрузки/connectorSQL/include/jdbc/cppconn)
target_link_libraries(${PROJECT_NAME} PRIVATE /home/xink/Загрузки/connectorSQL/lib64/libmysqlcppconn.so.9.8.0.28
        /home/xink/Загрузки/connectorSQL/lib64/private/libssl.so
        /home/xink/Загрузки/connectorSQL/lib64/private/libcrypto.so
        )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_range_for)
