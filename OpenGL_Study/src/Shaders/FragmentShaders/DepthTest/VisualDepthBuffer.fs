#version 330 core
out vec4 FragColor;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    // 线性，可以让片段非线性的深度值变换为线性的（反转深度值的投影变换）。
    // 1. 首先将深度值从[0, 1]范围重新变换到[-1, 1]范围的标准化设备坐标（NDC）（裁剪空间）。
    // 2. 接下来我们需要像投影矩阵那样反转这个非线性方程（方程2），并将这个反转的方程应用到最终的深度值上（最终的结果就是一个线性的深度值）。
    float z = depth * 2.0 - 1.0; // 将深度值变换为NDC
    float linearDepth = (2.0 * near * far) / (far + near - z * (far - near)); // 这个方程是用投影矩阵推导得出的，它使用了方程2来非线性化深度值，返回一个near与far之间的深度值。
    return linearDepth;
}

void main()
{
    // 非线性，屏幕空间中的深度值是非线性的，即它在z值很小的时候有很高的精度，而z值很大的时候有较低的精度。
    // 片段的深度值会随着距离迅速增加，所以几乎所有的顶点的深度值都是接近于1.0的。
    // 如果我们小心地靠近物体，你可能会最终注意到颜色会渐渐变暗，显示它们的z值在逐渐变小
    // 深度值的非线性性质：近处的物体比起远处的物体对深度值有着更大的影响，只需要移动几厘米就能让颜色从暗完全变白。
    // FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

    // 线性
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far，因为深度值的范围是0.1的近平面到100的远平面，它离我们还是非常远的。结果就是，我们相对靠近近平面，所以会得到更低的（更暗的）深度值。
    FragColor = vec4(vec3(depth), 1.0);
}
