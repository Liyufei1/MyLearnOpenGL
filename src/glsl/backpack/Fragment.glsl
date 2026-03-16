#version 330 core

struct Material {
    sampler2D diffuse; 
    sampler2D specular;
    float shininess;   
}; 

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 uCameraPos;
uniform Material uMaterial;


out vec4 FragColor;

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(uCameraPos - FragPos);
    vec3 result = vec3(0.0);

    FragColor = texture(uMaterial.diffuse, TexCoord.xy) * 3.0;
    // FragColor = vec4(1,0,0,0);
}