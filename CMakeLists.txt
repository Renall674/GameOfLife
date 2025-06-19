cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

#укажите ваш путь
set(SDL2_DIR "C:/GameOfLife/libs/SDL2/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#также ваш путь
add_executable(GameOfLife "C:/GameOfLife/src/Source.cpp")

target_link_libraries(GameOfLife ${SDL2_LIBRARIES})
