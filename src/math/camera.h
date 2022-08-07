#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#define CAMERA_UP glm::vec3(0.0, 1.0, 0.0)

class Camera {
public:
  Camera(glm::vec3 position, glm::vec3 rotation, int width, int height);
  glm::mat4 getProjectionMatrix();
  glm::mat4 getViewMatrix();
private:
  glm::vec3 position, rotation;
  int width, height;
};

#endif // CAMERA_H
