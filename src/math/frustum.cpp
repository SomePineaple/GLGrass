#include "frustum.h"

Frustum createFrustumFromCamera(const Camera &cam, float zNear, float zFar) {
  Frustum frustum;

  const glm::vec3 cameraPos = cam.getPosition();
  const glm::vec3 cameraDir = cam.getDirection();
  const glm::vec3 cameraRight = cam.getRightVector();

  const float halfVSide = zFar * tanf(CAMERA_FOV * 0.5f);
  const float halfHSide = halfVSide * cam.getAspect();
  const glm::vec3 frontMultFar = zFar * cameraDir;

  frustum.nearFace = { cameraPos + zNear * cameraDir, cameraDir };
  frustum.farFace = { cameraPos + frontMultFar, -cameraDir };
  frustum.rightFace = { cameraPos, glm::cross(CAMERA_UP, frontMultFar + cameraRight * halfHSide) };
  frustum.leftFace = { cameraPos, glm::cross(frontMultFar - cameraRight * halfHSide, CAMERA_UP) };
  frustum.topFace = { cameraPos, glm::cross(cameraRight, frontMultFar - CAMERA_UP * halfVSide) };
  frustum.bottomFace = { cameraPos, glm::cross(frontMultFar + CAMERA_UP * halfVSide, cameraRight) };

  return frustum;
}

float Plan::getSignedDistanceToPlan(const glm::vec3 &point) const {
  return glm::dot(normal, point) - distance;
}

bool AABB::isOnFrustum(const Frustum &frustum) const {
  return (
    isOnOrForwardPlan(frustum.leftFace) &&
    isOnOrForwardPlan(frustum.rightFace) &&
    isOnOrForwardPlan(frustum.topFace) && 
    isOnOrForwardPlan(frustum.bottomFace) &&
    isOnOrForwardPlan(frustum.nearFace) &&
    isOnOrForwardPlan(frustum.farFace)
  );
}

bool AABB::isOnOrForwardPlan(const Plan &plan) const {
  const float r = extents.x * std::abs(plan.normal.x) + 
                  extents.y * std::abs(plan.normal.y) +
                  extents.z * std::abs(plan.normal.z);

  return -r <= plan.getSignedDistanceToPlan(center);
}
