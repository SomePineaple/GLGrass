#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "utils/shader.h"
#include "mesh/mesh.h"
#include "math/camera.h"

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to init GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  GLFWwindow * window = glfwCreateWindow(800, 800, "GLGrass", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (gl3wInit()) {
    std::cerr << "Failed to init gl3w" << std::endl;
    return EXIT_FAILURE;
  }

  Shader mainShader("assets/mainVertex.glsl", "assets/mainFragment.glsl");
  Mesh floorMesh("assets/plane.obj");
  Camera mainCamera(glm::vec3(-1, 1, 0), glm::vec3(1, 0, 0), 800, 800);

  unsigned int projectionLocation = mainShader.getUniformLocation("projMatrix");
  unsigned int viewLocation = mainShader.getUniformLocation("viewMatrix");

  glClearColor(0.3, 0.5, 0.8, 1.0);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    mainShader.bind();
    mainShader.setMat4(projectionLocation, mainCamera.getProjectionMatrix());
    mainShader.setMat4(viewLocation, mainCamera.getViewMatrix());

    floorMesh.bind();

    floorMesh.render();

    floorMesh.unbind();
    mainShader.unbind();

    glfwSwapBuffers(window);
  }
  return EXIT_SUCCESS;
}
