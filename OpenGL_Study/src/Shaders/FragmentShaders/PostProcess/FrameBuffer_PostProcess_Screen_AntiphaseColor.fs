#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    // 反相 - 从屏幕纹理中取颜色值，然后用1.0减去它，对它进行反相
    FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);;
} 