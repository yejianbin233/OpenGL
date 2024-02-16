#version 330 core
layout(location=0) in vec3 aPos;

uniform mat4 model; // 模型矩阵
uniform mat4 view; // 视图矩阵
uniform mat4 projection; // 投影矩阵

out vec4 vCol; // 输出顶点颜色（位置数据作为顶点颜色）

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    vCol = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);
}