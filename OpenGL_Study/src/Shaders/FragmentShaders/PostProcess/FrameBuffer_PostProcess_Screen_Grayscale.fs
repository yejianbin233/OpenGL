#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    // 灰度，移除场景中除了黑白灰以外所有的颜色，让整个图像灰度化(Grayscale) - 取所有的颜色分量，将它们平均化
    // FragColor = texture(screenTexture, TexCoords);
    // float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
    // FragColor = vec4(average, average, average, 1.0);

    // 升级：人眼会对绿色更加敏感一些，而对蓝色不那么敏感，所以为了获取物理上更精确的效果，我们需要使用加权的(Weighted)通道（加重绿色通道占比，减少蓝色通道占比）
    FragColor = texture(screenTexture, TexCoords);
    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    FragColor = vec4(average, average, average, 1.0);
} 