cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
project (terrain_generator)

# needed for autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)
file(GLOB_RECURSE SOURCES source/*.cpp)
set(EXECUTABLE_NAME "terrain_generator")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# SFML setup 
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# OpengGL setup
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND) 
  include_directories(${OPENGL_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
endif()

# GLEW setup
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARIES})
endif()