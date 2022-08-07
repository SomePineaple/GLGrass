#include "shader.h"

#include <GL/gl3w.h>
#include <cstdlib>
#include <iostream>

#include "utils.h"

Shader::Shader(const char * vertPath, const char * fragPath) {
  unsigned int vertexShaderID = createShader(vertPath, GL_VERTEX_SHADER);
  unsigned int fragmentShaderID = createShader(fragPath, GL_FRAGMENT_SHADER);

  shaderProgramID = glCreateProgram();
  glAttachShader(shaderProgramID, vertexShaderID);
  glAttachShader(shaderProgramID, fragmentShaderID);
  
  glLinkProgram(shaderProgramID);

  int success;
  glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
  if (!success) {
    int logLength;
    glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
    char * infoLog = (char *) malloc(logLength);
    glGetProgramInfoLog(shaderProgramID, logLength, &logLength, infoLog);
    std::cerr << "Failed to link program: " << infoLog << std::endl;
    free(infoLog);
  }

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

unsigned int Shader::createShader(const char * path, unsigned int type) {
  char * source = Utils::readFileToString(path);
  unsigned int shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &source, nullptr);
  glCompileShader(shaderID);
  free(source);

  int success;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    int logLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    char * infoLog = (char *) malloc(logLength);
    glGetShaderInfoLog(shaderID, logLength, &logLength, infoLog);
    std::cerr << "ERROR: Failed to compile shader: " << infoLog << std::endl;
    free(infoLog);
  }

  return shaderID;
}
