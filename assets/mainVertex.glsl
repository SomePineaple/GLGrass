#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

void main() {
  gl_Position = projMatrix * viewMatrix * vec4(position, 1.0);
}
