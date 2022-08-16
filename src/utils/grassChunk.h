#ifndef GRASSCHUNK_H
#define GRASSCHUNK_H

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <vector>
#include <random>

#include "../math/camera.h"
#include "../math/frustum.h"
#include "../mesh/mesh.h"

class GrassChunk {
public:
  GrassChunk(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity);
  void render(const Mesh &grassMesh, const Frustum &camFrustum);
  [[nodiscard]] float getDistanceFromCamera(const glm::vec3 &cameraPos) const;
private:
  long numGrassBlades;
  AABB chunkBoundingBox;
  glm::vec2 * grassPositions;
};

#endif // GRASSCHUNK_H
