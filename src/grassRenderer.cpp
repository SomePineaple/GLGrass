#include "grassRenderer.h"

#include <GL/gl3w.h>
#include <random>

GrassRenderer::GrassRenderer(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity) : 
  grassShader("assets/grassVertex.glsl", "assets/grassFragment.glsl"), grassMesh("assets/grass.obj") {


  projectionMatrixUBO = grassShader.getUniformLocation("projMatrix");
  viewMatrixUBO = grassShader.getUniformLocation("viewMatrix");

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(-scarcity/2.0f, scarcity/2.0f);
  
  for (float y = grassStart.y; y < grassStop.y; y += scarcity) {
    for (float x = grassStart.x; x < grassStop.x; x += scarcity) {
      grassPositions.push_back(glm::vec2(x + distr(eng), y + distr(eng)));
    }
  }

  glGenBuffers(1, &positionsSSBO);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionsSSBO);
  glBufferData(GL_SHADER_STORAGE_BUFFER, grassPositions.size() * sizeof(glm::vec2), grassPositions.data(), GL_STATIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionsSSBO);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void GrassRenderer::renderGrass(Camera &camera) {
  grassShader.bind();
  grassShader.setMat4(projectionMatrixUBO, camera.getProjectionMatrix());
  grassShader.setMat4(viewMatrixUBO, camera.getViewMatrix());

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionsSSBO);
  grassMesh.bind();
  grassMesh.renderInstanced(grassPositions.size());
  grassMesh.unbind();
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  grassShader.unbind();
}
