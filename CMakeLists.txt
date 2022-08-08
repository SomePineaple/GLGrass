cmake_minimum_required(VERSION 3.20)

project(glgrass)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory("dependencies/glfw")
add_subdirectory("dependencies/glm")
add_subdirectory("dependencies/gl3w")

add_executable(glgrass src/main.cpp src/utils/shader.h src/utils/shader.cpp 
               src/utils/utils.h src/utils/utils.cpp src/math/camera.h 
               src/math/camera.cpp src/mesh/mesh.h src/mesh/mesh.cpp
               src/grassRenderer.h src/grassRenderer.cpp src/utils/grassChunk.h
               src/utils/grassChunk.cpp src/math/frustum.h src/math/frustum.cpp)

target_link_libraries(glgrass PUBLIC glfw glm gl3w)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ./)
