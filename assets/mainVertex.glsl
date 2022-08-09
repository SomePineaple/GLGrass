#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

out vec3 vertexNormal;
out vec4 eyeSpacePosition;

void main() {
  gl_Position = projMatrix * viewMatrix * vec4(position, 1.0);
  vertexNormal = normal;

  eyeSpacePosition = viewMatrix * vec4(position, 1.0);
}
