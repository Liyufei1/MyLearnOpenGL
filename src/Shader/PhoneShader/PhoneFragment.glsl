#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 TestColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // FragColor = TestColor;
    FragColor = mix(texture(uTexture0, TexCoord.xy),texture(uTexture1, TexCoord.xy),0.8f);
    // FragColor = vec4(TexCoord.xy, 0.0f, 1.0f);
} 