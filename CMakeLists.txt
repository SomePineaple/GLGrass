cmake_minimum_required(VERSION 3.20)

project(glgrass)

add_subdirectory("dependencies/glfw")
add_subdirectory("dependencies/glm")
add_subdirectory("dependencies/gl3w")

add_executable(glgrass src/main.cpp src/utils/shader.h src/utils/shader.cpp 
               src/utils/utils.h src/utils/utils.cpp src/math/camera.h 
               src/math/camera.cpp src/mesh/mesh.h src/mesh/mesh.cpp)

target_link_libraries(glgrass PUBLIC glfw glm gl3w)
