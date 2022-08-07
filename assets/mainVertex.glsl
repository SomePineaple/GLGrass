#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

out vec3 vertexNormal;

void main() {
  gl_Position = projMatrix * viewMatrix * vec4(position, 1.0);
  vertexNormal = normal;
}
