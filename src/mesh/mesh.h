#ifndef MESH_H
#define MESH_H

#include "../utils/utils.h"

class Mesh {
public:
  explicit Mesh(const char * objPath);
  void bind() const;
  void render() const;
  void renderInstanced(unsigned int instanceCount) const;
  static void unbind() ;
private:
  std::vector<Utils::Vertex> vertices;
  unsigned int vaoID = 0;
};

#endif // MESH_H
