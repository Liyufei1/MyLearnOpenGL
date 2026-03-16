#version 330  core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTangent;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec2 aUV;
layout (location = 5) in vec2 aUV1;
layout (location = 6) in vec2 aUV2;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewProjectionMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main(){
    FragPos = vec3(uModelMatrix * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
    TexCoord = aUV;

    gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPos, 1.0f);
}