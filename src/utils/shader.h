#ifndef SHADER_H
#define SHADER_H

class Shader {
public:
  Shader(const char * vertPath, const char * fragPath);
  void bind();
  void unbind();
private:
  unsigned int createShader(const char * path, unsigned int type);

  unsigned int shaderProgramID;
};

#endif // SHADER_H
