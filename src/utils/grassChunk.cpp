#include "grassChunk.h"

GrassChunk::GrassChunk(glm::vec2 grassStart, glm::vec2 grassStop, float scarcity) 
    : chunkBoundingBox(glm::vec3(grassStart.x, 0, grassStart.y), glm::vec3(grassStop.x, 1, grassStop.y)) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(-scarcity/2.0f, scarcity/2.0f);

  const glm::vec2 area = glm::abs(grassStop - grassStart);
  numGrassBlades = (area.x / scarcity) * (area.y / scarcity);

  grassPositions = new glm::vec2[numGrassBlades];
  
  unsigned int bladeNumber = 0;
  for (float y = grassStart.y; y < grassStop.y; y += scarcity) {
    for (float x = grassStart.x; x < grassStop.x; x += scarcity) {
      grassPositions[bladeNumber] = glm::vec2(x + distr(eng), y + distr(eng));
      bladeNumber++;
      if (bladeNumber >= numGrassBlades)
        return;
    }
  }
}

void GrassChunk::render(const Mesh &grassMesh, const Frustum &camFrustum) {
  if (!chunkBoundingBox.isOnFrustum(camFrustum))
    return;

  glBufferData(GL_SHADER_STORAGE_BUFFER, numGrassBlades * sizeof(glm::vec2), grassPositions, GL_STATIC_DRAW);
  grassMesh.renderInstanced(numGrassBlades);
}
