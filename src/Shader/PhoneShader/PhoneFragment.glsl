#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 TestColor;
in vec3 oNormal;
in vec3 oFragPos;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;


void main()
{
    // lightColor * texture(uTexture0, TexCoord.xy);
    float ambient = 0.3f ;
    float diffuse = 0.9f *  max(dot(normalize(oNormal), normalize(lightPos - oFragPos)), 0.0f);
    float specular = 0.9f *  pow(max(dot(normalize(cameraPos - oFragPos), normalize(lightPos - oFragPos)), 0.0f), 32.0f);


    // FragColor = vec4(TexCoord.xy, 0.0f, 1.0f);
    // FragColor = mix(texture(uTexture0, TexCoord.xy),texture(uTexture1, TexCoord.xy),0.8f);
    // FragColor = vec4((ambient + diffuse + specular) * lightColor * texture(uTexture0, TexCoord.xy).rgb, 1.0f);
    FragColor = vec4(( specular) * lightColor * texture(uTexture0, TexCoord.xy).rgb, 1.0f);

} 