#version 430 core

layout (location = 0) in vec3 position;

layout (std430, binding = 0) buffer positionsBuffer {
  vec2 grassPositions[];
};

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

out float height;

void main() {
  vec2 grassPosition = grassPositions[gl_InstanceID];

  gl_Position = projMatrix * viewMatrix * vec4(position.x + grassPosition.x, position.y, position.z + grassPosition.y, 1.0);

  height = position.y / 0.06;
}
