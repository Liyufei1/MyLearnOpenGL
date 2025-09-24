#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 TestColor;
in vec3 oNormal;
in vec3 oFragPos;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Light uLight = Light(vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 0.1f, 0.1f), vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f));
uniform Material uMaterial;
uniform vec3 uCameraPos;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;


void main()
{
    vec3 normal = normalize(oNormal);
    vec3 lightDir = normalize(uLight.position - oFragPos);
    vec3 viewDir = normalize(uCameraPos - oFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  

    vec3 ambient = uLight.ambient * texture(uMaterial.diffuse, TexCoord.xy).rgb ;
    vec3 diffuse = max(dot(normal, lightDir), 0.0f) * uLight.diffuse * texture(uMaterial.diffuse, TexCoord.xy).rgb;
    vec3 specular = pow(max(dot(reflectDir,viewDir), 0.0f), uMaterial.shininess) * uLight.specular * uMaterial.specular;


    // FragColor = vec4(normal, 1.0f);
    FragColor = vec4((ambient + diffuse + specular), 1.0f);

} 