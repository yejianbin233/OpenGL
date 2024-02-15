#version 330 core
// 插值
layout(location=0) in vec3 aPos;

uniform mat4 transform;

out vec4 vCol; // 输出顶点颜色（位置数据作为顶点颜色）


void main(){
    gl_Position = transform * vec4(0.4f*aPos.x, 0.4f*aPos.y, 0.4f*aPos.z, 1.0f);
    // 顶点之间的颜色会自动进行插值处理。
    vCol = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);
}