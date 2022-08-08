#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

namespace Utils {
  char * readFileToString(const char *);
  unsigned long currentTimeMillis();
  float randFloat(float min, float max);

  struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
  };

  struct VertRef {
    VertRef(int v, int vt, int vn) : v(v), vt(vt), vn(vn) { }
    int v, vt, vn;
  };

  std::vector<Vertex> loadOBJ(std::istream& in);
}

#endif // UTILS_h
