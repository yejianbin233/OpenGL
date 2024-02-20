#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture; // 自定义帧缓冲，作为后期处理数据

void main()
{
    // 采样帧缓冲数据
    vec3 col = texture(screenTexture, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
} 