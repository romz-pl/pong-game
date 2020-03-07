cmake_minimum_required (VERSION 3.0)

project (pong-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(3rdparty)
add_subdirectory(src)

