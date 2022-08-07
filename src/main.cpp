#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

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

  glClearColor(0.3, 0.5, 0.8, 1.0);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
  }
  return EXIT_SUCCESS;
}
