#include <iostream>

#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to init GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  GLFWwindow * window = glfwCreateWindow(800, 800, "GLGrass", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
  return EXIT_SUCCESS;
}
