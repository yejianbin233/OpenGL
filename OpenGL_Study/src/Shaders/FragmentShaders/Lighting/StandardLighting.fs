#version 330 core
out vec4 FragColor;

in vec3 Normal;  // 法线
in vec3 FragPos; // 表面点（光线照射到物体表面的位置）
  
uniform vec3 viewPos; // 视角位置（观察位置/摄像机位置）
uniform vec3 lightPos; // 灯光位置
uniform vec3 lightColor; // 灯光颜色
uniform vec3 objectColor; // 物体颜色

void main()
{
    // ambient - 环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor; // 光源强度 * 环境光强度（环境光率）

    // diffuse - 漫反射，朗伯余弦定律（根据光源方向计算光源辐照度）
    vec3 norm = normalize(Normal); // 归一化法线（防止错误的法线数据）
    vec3 lightDir = normalize(lightPos - FragPos); // L 光向量
    float diff = max(dot(norm, lightDir), 0.0); // 漫反射率，兰伯特光照模型
    vec3 diffuse = diff * lightColor; // 漫反射值

    // specular - 高光反射
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specularStrength = 0.5; // 高光反射强度
    vec3 viewDir = normalize(viewPos - FragPos);   // 表面位置指向视角的方向
    vec3 reflectDir = reflect(-lightDir, norm); // 反射方向
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // Phong 光照模型
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 