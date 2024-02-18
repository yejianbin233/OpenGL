#version 330 core
out vec4 FragColor;

// 材质属性
struct Material {
    // 使用灯光贴图（LightingMap）
    sampler2D diffuse; // 漫反射贴图
    sampler2D specular; // 高光贴图
    float shininess; // 光泽度
}; 

// 灯光属性（定向光源）
struct DirLight {
    // vec3 position; // 定向光源不需要光源位置
    
    vec3 direction; // 光源方向
    vec3 ambient; // 光源营造的环境光
    vec3 diffuse; // 光源漫反射
    vec3 specular; // 光源高光
};

// 灯光属性（点光源）
struct PointLight {
    vec3 position; // 光源位置

    vec3 ambient; // 光源营造的环境光
    vec3 diffuse; // 光源漫反射
    vec3 specular; // 光源高光

    // 点光源衰减属性
    float constant; // 常数项通常保持为1.0，它的主要作用是保证分母永远不会比1小，否则的话在某些距离上它反而会增加强度，这肯定不是我们想要的效果。
    float linear;    // 一次项会与距离值相乘，以线性的方式减少强度。
    float quadratic; // 二次项会与距离的平方相乘，让光源以二次递减的方式减少强度。二次项在距离比较小的时候影响会比一次项小很多，但当距离值比较大的时候它就会比一次项更大了。
};

// 灯光属性（聚光源）
struct SpotLight {
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

#define NR_POINT_LIGHTS 4 // 使用了预处理指令来定义了我们场景中点光源的数量

in vec3 FragPos; // 表面点（光线照射到物体表面的位置）
in vec3 Normal;  // 法线
in vec2 TexCoords; // UV（纹理坐标）

uniform vec3 viewPos; // 视角位置（观察位置/摄像机位置）
uniform Material material; // 材质属性

uniform DirLight dirLight;// 定向光源
uniform PointLight pointLights[NR_POINT_LIGHTS]; // 点光源
uniform SpotLight spotLight; // 聚光源

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);// 计算定向光源光照
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); // 计算点光源光照
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir); // 计算聚光源光照


void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting - 定向光源
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // // phase 2: point lights - 多个点光源
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light - 聚光源
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
     vec3 lightDir = normalize(-light.direction); // 光向量

     // 物体材质的漫反射率
     vec3 materialDiffuse = vec3(texture(material.diffuse, TexCoords));
     // 物体材质的高光反射率
     vec3 materialSpecular = vec3(texture(material.specular, TexCoords));

     // 环境光
     vec3 ambient = light.ambient * materialDiffuse;    

     // 漫反射
     float diff = max(dot(normal, lightDir), 0);
     vec3 diffuse = light.diffuse * diff * materialDiffuse;

     vec3 reflectDir = reflect(-lightDir, normal); // 反射方向
     float spec = pow(max(dot(viewDir, reflectDir), 0) , material.shininess); // 高光反射率
     vec3 specular = light.specular * spec * materialSpecular; // 高光反射值

     // 定向光源光量组合
     return ambient + diffuse + specular;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
     vec3 lightDir = normalize(light.position - fragPos); // 光向量
     
     // 物体材质的漫反射率
     vec3 materialDiffuse = vec3(texture(material.diffuse, TexCoords));
     // 物体材质的高光反射率
     vec3 materialSpecular = vec3(texture(material.specular, TexCoords));

     // 环境光
     vec3 ambient = light.ambient * materialDiffuse;

     // 漫反射
     float diff = max(dot(normal, lightDir), 0);
     vec3 diffuse = light.diffuse * diff * materialDiffuse;

     // 高光反射
     vec3 reflectDir = reflect(-lightDir, normal); // 反射方向
     float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess); // 高光反射值
     vec3 specular = light.specular * spec * materialSpecular;

     // 光照衰减
     float distance = length(light.position - fragPos); // 距离
     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); // 距离反平方
     
     // 应用光照衰减
     ambient *= attenuation;
     diffuse *= attenuation;
     specular *= attenuation;
     
      // 点光源光量组合
     return ambient + diffuse + specular;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}