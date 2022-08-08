#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>

#include "camera.h"

struct Plan {
  glm::vec3 normal = { 0.0f, 1.0f, 0.0f };
  float distance = 0.0f;

  Plan() = default;
  Plan(const glm::vec3& p1, const glm::vec3& norm)
    : normal(glm::normalize(norm)),
      distance(glm::dot(normal, p1)) {}
  
  float getSignedDistanceToPlan(const glm::vec3 &point) const;
};

struct Frustum {
  Plan topFace;
  Plan bottomFace;

  Plan rightFace;
  Plan leftFace;

  Plan farFace;
  Plan nearFace;
};

struct AABB {
  glm::vec3 center = { 0.0f, 0.0f, 0.0f };
  glm::vec3 extents = { 0.0f, 0.0f, 0.0f };

  AABB(const glm::vec3 &min, const glm::vec3 &max) 
    : center{ (max + min) * 0.5f },
      extents{ max.x - center.x, max.y - center.y, max.z - center.z } {};
  
  bool isOnFrustum(const Frustum &frustum) const;
  bool isOnOrForwardPlan(const Plan &plan) const;
};

Frustum createFrustumFromCamera(const Camera &cam, float zNear, float zFar);

#endif // FRUSTUM_H
