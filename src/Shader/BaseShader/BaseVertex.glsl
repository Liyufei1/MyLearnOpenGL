#version 330  core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTangent;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec2 aUV;
layout (location = 5) in vec2 aUV1;
layout (location = 6) in vec2 aUV2;

uniform mat4 uModelMatrix;
uniform mat4 uViewProjectionMatrix;
uniform vec4 uBaseColor = vec4(1.0, 1.0, 1.0, 1.0); // 默认白色

out vec4 BaseColor;

void main(){
    BaseColor = uBaseColor;
    gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPos, 1.0f);
}