#version 430 core

in vec3 vertexNormal;

out vec4 FragColor;

const vec3 dirtColor = vec3(0.37, 0.87, 0.17);

void main() {
  FragColor = vec4(dirtColor, 1);
}
