#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

// 在几何着色器中声明相同的接口块（使用一个不同的接口名），接收来自"顶点着色器"的颜色数据
in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

void build_house(vec4 position)
{    
    fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left   
    EmitVertex();
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0); // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0); // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0); // 5:top
    fColor = vec3(1.0, 1.0, 1.0); // 指定顶部顶点的颜色为白色。
    EmitVertex();
    EndPrimitive(); 
    // 使用 EmitVertex 和 EndPrimitive，来生成新的数据
    // EmitVertex 创建新的顶点
    // EndPrimitive 将所有新建的(Emitted)顶点都会合成为指定的输出渲染图元。
}

void main() {    
    build_house(gl_in[0].gl_Position);
}