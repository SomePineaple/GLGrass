#version 430 core

in vec3 vertexNormal;

out vec4 FragColor;

const vec3 dirtColor = vec3(1);

void main() {
  FragColor = vec4(dirtColor, 1);
}
