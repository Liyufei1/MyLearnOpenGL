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
uniform float Test;


out vec4 TestColor;
out vec2 TexCoord;

out vec3 oNormal;
out vec3 oFragPos;

void main(){
    oNormal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
    oFragPos = vec3(uModelMatrix * vec4(aPos, 1.0f));

    // TestColor = vec4(Test,0.0f,0.0f, 1.0f);
    // TestColor = vec4(aNormal,1.0f);
    // TestColor = vec4(aTangent,1.0f);

    TexCoord = aUV;
    gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(aPos, 1.0f);
}