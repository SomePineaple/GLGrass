#include "grassRenderer.h"

#include <GL/gl3w.h>

GrassRenderer::GrassRenderer(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity) : 
  grassShader("assets/grassVertex.glsl", "assets/grassFragment.glsl"), grassMesh("assets/grass.obj") {

  projectionMatrixUBO = grassShader.getUniformLocation("projMatrix");
  viewMatrixUBO = grassShader.getUniformLocation("viewMatrix");
  
  for (float y = grassStart.y; y < grassStop.y; y += GRASS_CHUNK_SIZE) {
    for (float x = grassStart.x; x < grassStop.x; x += GRASS_CHUNK_SIZE) {
      grassChunks.push_back(GrassChunk(glm::vec2(x, y), glm::vec2(x + GRASS_CHUNK_SIZE, y + GRASS_CHUNK_SIZE), scarcity));
    }
  }

  std::cout << "Num chunks: " << grassChunks.size() << std::endl;
}

void GrassRenderer::renderGrass(const Camera &camera) {
  Frustum camFrustum = createFrustumFromCamera(camera, CAMERA_ZNEAR, CAMERA_ZFAR);

  grassShader.bind();
  grassShader.setMat4(projectionMatrixUBO, camera.getProjectionMatrix());
  grassShader.setMat4(viewMatrixUBO, camera.getViewMatrix());

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionsSSBO);
  grassMesh.bind();
  for (GrassChunk chunk : grassChunks)
    chunk.render(grassMesh, camFrustum);
  grassMesh.unbind();
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  grassShader.unbind();
}
