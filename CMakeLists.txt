cmake_minimum_required(VERSION 3.1)
project(getfilepath)
find_package(Boost COMPONENTS  filesystem   REQUIRED)
add_definitions(-std=c++11)
set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/include)
include_directories(/usr/include/yaml-cpp)

set(SRCS ${PROJECT_SOURCE_DIR})
add_executable(getfilepath ${PROJECT_SOURCE_DIR}/src/getfilepath.cpp)
target_link_libraries(getfilepath /usr/local/lib/libyaml-cpp.so)
target_link_libraries(getfilepath 
      ${Boost_FILESYSTEM_LIBRARY}
      ${Boost_SYSTEM_LIBRARY}
      #${PROTOBUF_LIBRARY}
    )

