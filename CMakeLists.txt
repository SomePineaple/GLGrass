cmake_minimum_required(VERSION 3.20)

project(glgrass)

add_subdirectory("dependencies/glfw")
add_subdirectory("dependencies/glm")

add_executable(glgrass src/main.cpp)
target_link_libraries(glgrass PUBLIC glfw glm)
