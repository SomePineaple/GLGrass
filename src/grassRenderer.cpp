#include "grassRenderer.h"

GrassRenderer::GrassRenderer(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity) : 
  grassShader("assets/grassVertex.glsl", "assets/grassFragment.glsl"), grassMesh("assets/grass.obj"), lowPolyGrassMesh("assets/grassTriangle.obj") {

  projectionMatrixUBO = grassShader.getUniformLocation("projMatrix");
  viewMatrixUBO = grassShader.getUniformLocation("viewMatrix");
  timeUBO = grassShader.getUniformLocation("time");

  positionsSSBO = 0;

  startTime = Utils::currentTimeMillis();
  
  for (float y = grassStart.y; y < grassStop.y; y += GRASS_CHUNK_SIZE) {
    for (float x = grassStart.x; x < grassStop.x; x += GRASS_CHUNK_SIZE) {
      grassChunks.emplace_back(glm::vec2(x, y), glm::vec2(x + GRASS_CHUNK_SIZE, y + GRASS_CHUNK_SIZE), scarcity);
    }
  }

  std::cout << "Num chunks: " << grassChunks.size() << std::endl;

  glGenBuffers(1, &positionsSSBO);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionsSSBO);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionsSSBO);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void GrassRenderer::renderGrass(const Camera &camera) {
  Frustum camFrustum = createFrustumFromCamera(camera, CAMERA_ZNEAR, 7.0f);

  grassShader.bind();
  grassShader.setMat4(projectionMatrixUBO, camera.getProjectionMatrix());
  grassShader.setMat4(viewMatrixUBO, camera.getViewMatrix());
  grassShader.setFloat(timeUBO, (float)(Utils::currentTimeMillis() - startTime) / 1000.0f);

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionsSSBO);
  for (GrassChunk chunk : grassChunks) {
    if (chunk.getDistanceFromCamera(camera.getPosition()) < GRASS_LOD_CUTOFF_DISTANCE) {
      grassMesh.bind();
      chunk.render(grassMesh, camFrustum);
      grassMesh.unbind();
    } else {
      lowPolyGrassMesh.bind();
      chunk.render(lowPolyGrassMesh, camFrustum);
      lowPolyGrassMesh.unbind();
    }
  }

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  grassShader.unbind();
}
