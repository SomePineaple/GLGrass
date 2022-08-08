#version 430 core

in float height;

out vec4 FragColor;

void main() {
  FragColor = vec4(mix(vec3(0.2, 0.2, 0.5), vec3(0.8, 0.2, 0.2), vec3(height)), 1);
}
