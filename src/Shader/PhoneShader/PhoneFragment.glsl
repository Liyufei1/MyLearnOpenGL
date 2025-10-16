#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse; 
    sampler2D specular;
    float shininess;   
}; 

struct DirLight {
    vec3 direction;    

    vec3 ambient;       
    vec3 diffuse;       
    vec3 specular;     
};

struct PointLight {
    vec3 position;     

    float constant;     
    float linear;       
    float quadratic;    

    vec3 ambient;       
    vec3 diffuse;       
    vec3 specular;      
};

struct SpotLight {
    vec3 position;      
    vec3 direction;     
    float cutOff;       
    float outerCutOff;  

    float constant;     
    float linear;       
    float quadratic;    

    vec3 ambient;       
    vec3 diffuse;       
    vec3 specular;      
};

#define POINT_LIGHTS_NUM 1
#define SPOT_LIGHTS_NUM 1

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 uCameraPos;
uniform Material uMaterial;

uniform DirLight uDirLight;
uniform PointLight uPointLights[POINT_LIGHTS_NUM];
uniform SpotLight uSpotLight[SPOT_LIGHTS_NUM];


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(uCameraPos - FragPos);

    vec3 result = vec3(0.0);
    // result += CalcDirLight(uDirLight, norm, viewDir);
    for(int i = 0; i < POINT_LIGHTS_NUM; i++)
    {
        result += CalcPointLight(uPointLights[i], norm, FragPos, viewDir);
    }
    // for(int i = 0; i < SPOT_LIGHTS_NUM; i++)
    // {
    //     result += CalcSpotLight(uSpotLight[i], norm, FragPos, viewDir);
    // }

    // FragColor = vec4(viewDir, 1.0f);
    // FragColor = vec4(norm, 1.0f);
    FragColor = vec4(result, 1.0f);

} 


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);  

    vec3 ambient = light.ambient * texture(uMaterial.diffuse, TexCoord.xy).rgb ;   
    vec3 diffuse = max(dot(normal, lightDir), 0.0f) * light.diffuse * texture(uMaterial.diffuse, TexCoord.xy).rgb;     
    vec3 specular = pow(max(dot(reflectDir,viewDir), 0.0f), uMaterial.shininess) * light.specular * texture(uMaterial.specular,TexCoord.xy).rgb;  

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * texture(uMaterial.diffuse, TexCoord.xy).rgb ;   
    vec3 diffuse = max(dot(normal, lightDir), 0.0f) * light.diffuse * texture(uMaterial.diffuse, TexCoord.xy).rgb;     
    vec3 specular = pow(max(dot(reflectDir,viewDir), 0.0f), uMaterial.shininess) * light.specular * texture(uMaterial.specular,TexCoord.xy).rgb; 

    return (ambient + diffuse + specular) * attenuation;
    // return (ambient + diffuse + specular);
    // return (ambient + specular);
    // return light.specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * texture(uMaterial.diffuse, TexCoord.xy).rgb ; 
    vec3 diffuse = max(dot(normal, lightDir), 0.0f) * light.diffuse * texture(uMaterial.diffuse, TexCoord.xy).rgb;  
    vec3 specular = pow(max(dot(reflectDir,viewDir), 0.0f), uMaterial.shininess) * light.specular * texture(uMaterial.specular,TexCoord.xy).rgb;

    return (ambient + diffuse + specular) * attenuation * intensity;
}