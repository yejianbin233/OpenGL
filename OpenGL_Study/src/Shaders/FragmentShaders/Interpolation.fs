#version 330 core
// 插值
in vec4 vCol; // 获取自定义的顶点颜色

out vec4 fragColor;

void main()
{
    fragColor = vCol;
}