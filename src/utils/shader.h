#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

class Shader {
public:
  Shader(const char * vertPath, const char * fragPath);

  int getUniformLocation(const char * uniformName) const;
  static void setMat4(int uniformLocation, glm::mat4 mat);
  static void setFloat(int uniformLocation, float value);

  void bind() const;
  static void unbind();
private:
  static unsigned int createShader(const char * path, unsigned int type);

  unsigned int shaderProgramID;
};

#endif // SHADER_H
