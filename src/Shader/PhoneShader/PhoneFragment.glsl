#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 TestColor;
in vec3 oNormal;
in vec3 oFragPos;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uCameraPos;


void main()
{
    vec3 normal = normalize(oNormal);
    vec3 lightDir = normalize(uLightPos - oFragPos);
    vec3 viewDir = normalize(uCameraPos - oFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  

    float ambient = 0.1f ;
    float diffuse = 0.6f *  max(dot(normal, lightDir), 0.0f);
    float specular = 0.9f *  pow(max(dot(reflectDir,viewDir), 0.0f), 32.0f);


    // FragColor = vec4(normal, 1.0f);
    // FragColor = mix(texture(uTexture0, TexCoord.xy),texture(uTexture1, TexCoord.xy),0.8f);
    // FragColor = vec4((ambient + diffuse + specular) * uLightColor * texture(uTexture0, TexCoord.xy).rgb, 1.0f);
    FragColor = vec4((ambient + diffuse + specular) * uLightColor * texture(uTexture0, TexCoord.xy).rgb, 1.0f);

} 