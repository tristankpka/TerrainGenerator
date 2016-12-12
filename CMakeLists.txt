cmake_minimum_required (VERSION 2.8.11)
project (terrain_generator)

# needed for autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# use C++11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set warning level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

set(SOURCES source/main.cpp source/Display.cpp)
add_executable(main ${SOURCES})

# SDL2 setup
set(SDL2_INCLUDE_DIR "/usr/local/include/SDL2")
set(SDL2_LIBRARY "/usr/local/lib/libSDL2.so")
target_include_directories(main PUBLIC "/usr/local/include/SDL2")
target_link_libraries(main "${SDL2_LIBRARY}")

# OpengGl setup
find_package(OpenGL REQUIRED) 
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(main ${OPENGL_LIBRARIES})

# GLEW setup
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(main ${GLEW_LIBRARIES})