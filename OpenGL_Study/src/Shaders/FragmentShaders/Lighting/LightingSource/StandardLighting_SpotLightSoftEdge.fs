#version 330 core
out vec4 FragColor;

// 材质属性
struct Material {
    // 使用灯光贴图（LightingMap）
    sampler2D diffuse; // 漫反射贴图
    sampler2D specular; // 高光贴图
    float shininess; // 光泽度
}; 

// 灯光属性（聚光源）
struct Light {
    vec3 position; // 光源位置

    vec3 ambient; // 光源营造的环境光
    vec3 diffuse; // 光源漫反射
    vec3 specular; // 光源高光

    // 光源衰减属性
    float constant; // 常数项通常保持为1.0，它的主要作用是保证分母永远不会比1小，否则的话在某些距离上它反而会增加强度，这肯定不是我们想要的效果。
    float linear;    // 一次项会与距离值相乘，以线性的方式减少强度。
    float quadratic; // 二次项会与距离的平方相乘，让光源以二次递减的方式减少强度。二次项在距离比较小的时候影响会比一次项小很多，但当距离值比较大的时候它就会比一次项更大了。

    // 聚光源特定属性
    vec3 direction; // 聚光源方向
    float cutOff; // 外切角
    float outerCutOff; // 内切角
};

in vec3 FragPos; // 表面点（光线照射到物体表面的位置）
in vec3 Normal;  // 法线
in vec2 TexCoords; // UV（纹理坐标）
  
uniform vec3 viewPos; // 视角位置（观察位置/摄像机位置）
uniform Material material; // 材质属性
uniform Light light; // 灯光属性

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    
    // spotlight (soft edges) - 聚光源边缘软化
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 