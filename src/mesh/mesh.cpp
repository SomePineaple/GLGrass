#include "mesh.h"

#include <fstream>
#include <GL/gl3w.h>

Mesh::Mesh(const char * objPath) {
  std::ifstream objStream(objPath);
  verticies = Utils::loadOBJ(objStream);
  objStream.close();

  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
  unsigned int vboID;
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Utils::Vertex), verticies.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unbind();
}

void Mesh::bind() {
  glBindVertexArray(vaoID);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void Mesh::render() {
  glDrawArrays(GL_TRIANGLES, 0, verticies.size());
}

void Mesh::unbind() {
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}
