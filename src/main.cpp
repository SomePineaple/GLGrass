#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "utils/shader.h"
#include "mesh/mesh.h"
#include "math/camera.h"
#include "grassRenderer.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to init GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLGrass", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  if (gl3wInit()) {
    std::cerr << "Failed to init gl3w" << std::endl;
    return EXIT_FAILURE;
  }

  Shader mainShader("assets/mainVertex.glsl", "assets/mainFragment.glsl");
  Mesh floorMesh("assets/plane.obj");
  GrassRenderer grassRenderer(glm::vec2(0, 0), glm::vec2(100, 100), 0.008);
  Camera mainCamera(glm::vec3(50, 0.2, 50), glm::vec3(1, 0, 0), WINDOW_WIDTH, WINDOW_HEIGHT);

  int projectionLocation = mainShader.getUniformLocation("projMatrix");
  int viewLocation = mainShader.getUniformLocation("viewMatrix");

  glClearColor(1, 1, 1, 1);

  unsigned long fps = 0;
  unsigned long lastFpsDisplay = 0;

  glEnable(GL_DEPTH_TEST);

  unsigned long lastFrameTime = 0;
  while (!glfwWindowShouldClose(window)) {
    double frameTime = ((double)Utils::currentTimeMillis() - (double) lastFrameTime) / 1000.0;
    lastFrameTime = Utils::currentTimeMillis();

    glfwPollEvents();

    mainCamera.updateCameraPosition(window, frameTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render floor
    mainShader.bind();
    Shader::setMat4(projectionLocation, mainCamera.getProjectionMatrix());
    // The view matrix for the floor doesn't include the camera's xy position, and so the camera is centered on the
    // floor at all times. This works because its just one flat square, and now we don't need it to be massive and cover
    // the entire field of grass.
    Shader::setMat4(viewLocation, Camera(glm::vec3(0, mainCamera.getPosition().y, 0), mainCamera.getDirection(), WINDOW_WIDTH, WINDOW_HEIGHT).getViewMatrix());

    floorMesh.bind();

    floorMesh.render();

    floorMesh.unbind();
    Shader::unbind();

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
