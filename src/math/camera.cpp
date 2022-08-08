#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 rotation, int width, int height) {
  this->position = position;
  this->rotation = rotation;
  this->width = width;
  this->height = height;
}

glm::mat4 Camera::getProjectionMatrix() const {
  return glm::perspectiveFov(90.0f, (float) width, (float) height, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + rotation, CAMERA_UP);
}
