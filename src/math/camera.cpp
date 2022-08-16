#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 direction, int width, int height) : position(position), direction(direction) {
  this->width = width;
  this->height = height;
}

void Camera::updateCameraPosition(GLFWwindow *window, double deltaTime) {
  float travelDistance = CAMERA_SPEED * (float) deltaTime;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    position += direction * travelDistance;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    position -= direction * travelDistance;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    position -= glm::normalize(glm::cross(direction, CAMERA_UP)) * travelDistance;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    position += glm::normalize(glm::cross(direction, CAMERA_UP)) * travelDistance;
}

void Camera::updateSize(int width, int height) {
  this->width = width;
  this->height = height;
}

glm::mat4 Camera::getProjectionMatrix() const {
  return glm::perspectiveFov(CAMERA_FOV, (float) width, (float) height, CAMERA_ZNEAR, CAMERA_ZFAR);
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + direction, CAMERA_UP);
}

float Camera::getAspect() const {
  return width / height;
}

glm::vec3 Camera::getDirection() const {
  return direction;
}

glm::vec3 Camera::getPosition() const {
  return position;
}

glm::vec3 Camera::getRightVector() const {
  return glm::cross(CAMERA_UP, direction);
}
