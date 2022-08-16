#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#define CAMERA_UP glm::vec3(0.0, 1.0, 0.0)
#define CAMERA_FOV 90.0f
#define CAMERA_ZNEAR 0.001f
#define CAMERA_ZFAR 100.0f
#define CAMERA_SPEED 0.3f

class Camera {
public:
  Camera(glm::vec3 position, glm::vec3 direction, int width, int height);

  void updateCameraPosition(GLFWwindow *window, double deltaTime);
  void updateSize(int width, int height);

  [[nodiscard]] glm::mat4 getProjectionMatrix() const;
  [[nodiscard]] glm::mat4 getViewMatrix() const;
  [[nodiscard]] float getAspect() const;
  [[nodiscard]] glm::vec3 getDirection() const;
  [[nodiscard]] glm::vec3 getPosition() const;
  [[nodiscard]] glm::vec3 getRightVector() const;
private:
  glm::vec3 position, direction;
  int width, height;
};

#endif // CAMERA_H
