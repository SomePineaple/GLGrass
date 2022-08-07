#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

class Shader {
public:
  Shader(const char * vertPath, const char * fragPath);

  unsigned int getUniformLocation(const char * uniformName);
  void setMat4(unsigned int uniformLocation, glm::mat4 mat);

  void bind();
  void unbind();
private:
  unsigned int createShader(const char * path, unsigned int type);

  unsigned int shaderProgramID;
};

#endif // SHADER_H
