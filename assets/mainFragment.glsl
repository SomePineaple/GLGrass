#version 430 core

struct FogParameters {
  vec3 color;
  float linearStart;
  float linearEnd;
  float density;

  int equation;
  bool isEnabled;
};

float getFogFactor(FogParameters params, float fogCoordinate) {
  float result = 0.0;
  if(params.equation == 0) {
    float fogLength = params.linearEnd - params.linearStart;
    result = (params.linearEnd - fogCoordinate) / fogLength;
  }
  else if(params.equation == 1) {
    result = exp(-params.density * fogCoordinate);
  }
  else if(params.equation == 2) {
    result = exp(-pow(params.density * fogCoordinate, 2.0));
  }

  result = 1.0 - clamp(result, 0.0, 1.0);
  return result;
}

in vec3 vertexNormal;
in vec4 eyeSpacePosition;

out vec4 FragColor;

const vec3 dirtColor = vec3(0, 0.2, 0);

const FogParameters fogParams = {
  vec3(1),
  7.0,
  10.0,
  0.7,
  1,
  true
};

void main() {
  FragColor = vec4(dirtColor, 1);

  if(fogParams.isEnabled) {
    float fogCoordinate = abs(eyeSpacePosition.z / eyeSpacePosition.w);
    FragColor = mix(FragColor, vec4(fogParams.color, 1.0), getFogFactor(fogParams, fogCoordinate));
  }
}
