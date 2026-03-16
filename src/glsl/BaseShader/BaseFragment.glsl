#version 330 core
out vec4 FragColor;

struct Material {
    vec3 diffuse; 
    vec3 specular;
    float shininess;   
}; 

in vec4 BaseColor;
uniform Material uMaterial;


void main()
{
    FragColor = vec4(uMaterial.diffuse,1.0f);
} 