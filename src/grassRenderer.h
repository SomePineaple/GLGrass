#ifndef GRASSRENDERER_H
#define GRASSRENDERER_H

#include <GL/gl3w.h>
#include <vector>
#include <glm/glm.hpp>

#include "utils/shader.h"
#include "math/camera.h"
#include "mesh/mesh.h"
#include "utils/grassChunk.h"

#define GRASS_CHUNK_SIZE 0.5f
#define GRASS_LOD_CUTOFF_DISTANCE 3.0f

class GrassRenderer {
public:
  GrassRenderer(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity);
  void renderGrass(const Camera &camera);
private:
  Shader grassShader;
  unsigned int positionsSSBO;
  unsigned int projectionMatrixUBO;
  unsigned int viewMatrixUBO;
  unsigned int timeUBO;

  unsigned long startTime;

  Mesh grassMesh;
  Mesh lowPolyGrassMesh;
  
  std::vector<GrassChunk> grassChunks;
};

#endif // GRASSRENDERER_H
