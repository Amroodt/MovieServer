cmake_minimum_required(VERSION 3.29)
project(ReceiveClient)


set(CMAKE_CXX_STANDARD 20)

# Use pkg-config to find pqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

find_package(nlohmann_json CONFIG REQUIRED)

include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})

add_executable(ReceiveClient main.cpp
        Movie.h
        Movie.cpp
        OMDbClient.h
        OMDbClient.cpp
        user.cpp
        user.h)

target_link_libraries(ReceiveClient PRIVATE nlohmann_json::nlohmann_json
        ${PQXX_LIBRARIES})
