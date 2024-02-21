#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = aPos; // 使用位置来作为 UV，用作立方体贴图的采样
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}