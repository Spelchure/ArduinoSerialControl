cmake_minimum_required(VERSION 3.6.3)

project(ArduinoSerialControl CXX)

set(ASC_SOURCES src/asc_main.cc)

set(CMAKE_CXX_STANDARD 17)
set(THREAD_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(ArduinoSerialControl ${ASC_SOURCES})

target_link_libraries(ArduinoSerialControl PRIVATE Threads::Threads)

