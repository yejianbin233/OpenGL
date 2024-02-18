#version 330 core
out vec4 FragColor;

// 材质属性
struct Material {
    // 使用灯光贴图（LightingMap）
    sampler2D diffuse; // 漫反射贴图
    sampler2D specular; // 高光贴图
    float shininess; // 光泽度
}; 

// 灯光属性
struct Light {
    vec3 position; // 光源位置
    vec3 ambient; // 光源营造的环境光
    vec3 diffuse; // 光源漫反射
    vec3 specular; // 光源高光
};

in vec3 FragPos; // 表面点（光线照射到物体表面的位置）
in vec3 Normal;  // 法线
in vec2 TexCoords; // UV（纹理坐标）
  
uniform vec3 viewPos; // 视角位置（观察位置/摄像机位置）
uniform Material material; // 材质属性
uniform Light light; // 灯光属性

void main()
{
    // ambient - 环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb; // 光源环境光 + 物体漫反射贴图颜色

    // diffuse - 漫反射，朗伯余弦定律（根据光源方向计算光源辐照度）
    vec3 norm = normalize(Normal); // 归一化法线（防止错误的法线数据）
    vec3 lightDir = normalize(light.position - FragPos); // L 光向量
    float diff = 0.5 * max(dot(norm, lightDir), 0.0) + 0.5; // 漫反射率，半兰伯特光照模型
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb; // 漫反射值
    
    // // specular - 高光反射
    // vec3 viewDir = normalize(viewPos - FragPos);   // 表面位置指向视角的方向
    // vec3 halfwayDir = normalize(lightDir + viewDir); // 半程方向
    // float spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess); // Blinn-Phong 光照模型
    // vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

     // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // Phong 光照模型
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 