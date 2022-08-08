#version 430 core

in vec3 vertexNormal;

out vec4 FragColor;

const vec3 dirtColor = vec3(104.0/255.0, 65.0/255.0, 29.0/255.0);

void main() {
  FragColor = vec4(dirtColor, 1);
}
