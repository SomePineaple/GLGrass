#ifndef GRASSCHUNK_H
#define GRASSCHUNK_H

#include <glm/glm.hpp>
#include <vector>

#include "../math/camera.h"
#include "../mesh/mesh.h"

class GrassChunk {
public:
  GrassChunk(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity);
  void render(const Mesh &grassMesh);
private:
  std::vector<glm::vec2> grassPositions;
  unsigned int positionsSSBO;
};

#endif // GRASSCHUNK_H
