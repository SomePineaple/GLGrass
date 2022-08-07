#ifndef GRASSRENDERER_H
#define GRASSRENDERER_H

#include <vector>
#include <glm/glm.hpp>

#include "utils/shader.h"
#include "math/camera.h"
#include "mesh/mesh.h"

class GrassRenderer {
public:
  GrassRenderer(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity);
  void renderGrass(Camera &camera);
private:
  Shader grassShader;
  unsigned int positionsSSBO;
  unsigned int projectionMatrixUBO;
  unsigned int viewMatrixUBO;

  Mesh grassMesh;
  
  std::vector<glm::vec3> grassPositions;
};

#endif // GRASSRENDERER_H
