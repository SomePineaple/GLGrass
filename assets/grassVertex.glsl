#version 430 core

layout (location = 0) in vec3 position;

layout (std430, binding = 0) buffer positionsBuffer {
  vec3 grassPositions[];
};

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

void main() {
  gl_Position = projMatrix * viewMatrix * vec4(position + grassPositions[gl_InstanceID], 1.0);
}
