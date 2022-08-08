#version 430 core

in float height;

out vec4 FragColor;

void main() {
  FragColor = vec4(mix(vec3(0, 0.3, 0), vec3(0, 1, 0), vec3(height)), 1);
}

