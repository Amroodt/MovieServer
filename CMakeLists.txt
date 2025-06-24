cmake_minimum_required(VERSION 3.29)
project(ReceiveClient)

set(CMAKE_CXX_STANDARD 20)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(ReceiveClient main.cpp
        Movie.h
        Movie.cpp
        OMDbClient.h
        OMDbClient.cpp)

target_link_libraries(ReceiveClient PRIVATE nlohmann_json::nlohmann_json)