cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main VERSION 1.0)

find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL REQUIRED)
include_directories(main ${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES board.cpp fps.cpp game.cpp)
add_executable(main main.cpp ${SRC_FILES})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PUBLIC ${SDL_INCLUDE_DIR}/include PUBLIC ${SDL2_INCLUDE_DIRS}/include PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}/include)
target_link_libraries(main ${SDL2_LIBRARIES} SDL2 SDL2_ttf)
