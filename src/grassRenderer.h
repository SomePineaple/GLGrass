#ifndef GRASSRENDERER_H
#define GRASSRENDERER_H

#include <GL/gl3w.h>
#include <vector>
#include <glm/glm.hpp>

#include "utils/shader.h"
#include "math/camera.h"
#include "mesh/mesh.h"
#include "utils/grassChunk.h"

#define GRASS_CHUNK_SIZE 1.0f

#define DEBUG_RENDER_CAMERA Camera(glm::vec3(0, 100, 0), glm::vec3(0, -1, 0), 800, 800)

class GrassRenderer {
public:
  GrassRenderer(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity);
  void renderGrass(const Camera &camera);
private:
  Shader grassShader;
  unsigned int positionsSSBO;
  unsigned int projectionMatrixUBO;
  unsigned int viewMatrixUBO;

  Mesh grassMesh;
  
  std::vector<GrassChunk> grassChunks;
};

#endif // GRASSRENDERER_H
