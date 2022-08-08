#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "utils/shader.h"
#include "mesh/mesh.h"
#include "math/camera.h"
#include "grassRenderer.h"

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to init GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow * window = glfwCreateWindow(800, 800, "GLGrass", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (gl3wInit()) {
    std::cerr << "Failed to init gl3w" << std::endl;
    return EXIT_FAILURE;
  }

  Shader mainShader("assets/mainVertex.glsl", "assets/mainFragment.glsl");
  Mesh floorMesh("assets/plane.obj");
  GrassRenderer grassRenderer(glm::vec2(-20, -2), glm::vec2(20, 20), 0.005);
  Camera mainCamera(glm::vec3(0, 0.3, 0), glm::vec3(1, 0, 0), 800, 800);

  unsigned int projectionLocation = mainShader.getUniformLocation("projMatrix");
  unsigned int viewLocation = mainShader.getUniformLocation("viewMatrix");

  glClearColor(0.3, 0.5, 0.8, 1.0);

  unsigned long fps = 0;
  unsigned long lastFpsDisplay = 0;

  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    mainCamera.updateCameraPosition(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render floor
    mainShader.bind();
    mainShader.setMat4(projectionLocation, mainCamera.getProjectionMatrix());
    mainShader.setMat4(viewLocation, mainCamera.getViewMatrix());

    floorMesh.bind();

    floorMesh.render();

    floorMesh.unbind();
    mainShader.unbind();

    // Render grass now
    grassRenderer.renderGrass(mainCamera);

    glfwSwapBuffers(window);

    fps++;
    if ((Utils::currentTimeMillis() - lastFpsDisplay) > 1000) {
      std::string title = "OpenGL Grass | FPS: ";
      title += std::to_string(fps);
      glfwSetWindowTitle(window, title.c_str());
      fps = 0;
      lastFpsDisplay = Utils::currentTimeMillis();
    }
  }
  return EXIT_SUCCESS;
}
