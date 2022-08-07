#ifndef MESH_H
#define MESH_H

#include "../utils/utils.h"

class Mesh {
public:
  Mesh(const char * objPath);
  void bind();
  void render();
  void unbind();
private:
  std::vector<Utils::Vertex> verticies;
  unsigned int vaoID;
};

#endif // MESH_H
