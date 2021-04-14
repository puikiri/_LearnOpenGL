#version 330 core
in vec2 TexCoord;
in vec3 Normal; // 法向量(世界)
in vec3 FragPos; // 顶点位置（世界）

out vec4 FragColor;

uniform vec3 viewPos; // 相机位置

struct Material { // 材质
    sampler2D diffuse;
    sampler2D specular;
    //vec4 ambient; // ambient材质向量定义了在环境光照下这个物体反射得是什么颜色，通常这是和物体颜色相同的颜色
    //vec4 diffuse; // diffuse材质向量定义了在漫反射光照下物体的颜色。（和环境光照一样）漫反射颜色也要设置为我们需要的物体颜色。
    //vec4 specular; // specular材质向量设置的是镜面光照对物体的颜色影响（或者甚至可能反射一个物体特定的镜面高光颜色）。
    float shininess; // shininess影响镜面高光的散射/半径。
}; 

struct Light {
	// 光的属性，见楼上
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

	// 定向光
    vec3 direction; 
	// 点光
	vec3 lightPos;
    float constant;
    float linear;
    float quadratic;
	// 聚光
	vec3 cameralightPos;
    vec3 cameraDirection;
    float cutOff;
	float outerCutOff;
};

uniform Material material;

struct DirLight {
    vec3 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};  
uniform DirLight dirLight;
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec4 ambient  = light.ambient  * vec4(texture(material.diffuse, TexCoord));
    vec4 diffuse  = light.diffuse  * diff * vec4(texture(material.diffuse, TexCoord));
    vec4 specular = light.specular * spec * vec4(texture(material.specular, TexCoord));
    return (ambient + diffuse + specular);
}

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};  
uniform PointLight pointLight;
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * (distance * distance));    
    // 合并结果
    vec4 ambient  = light.ambient  * vec4(texture(material.diffuse, TexCoord));
    vec4 diffuse  = light.diffuse  * diff * vec4(texture(material.diffuse, TexCoord));
    vec4 specular = light.specular * spec * vec4(texture(material.specular, TexCoord));

    return attenuation * (ambient + diffuse + specular);
}

struct SpotLight {
	// 聚光
	vec3 position;
    vec3 direction;
    float cutOff;
	float outerCutOff;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};
uniform SpotLight spotLight;
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	// 聚光的计算
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction)); 
	// 聚光外圈柔滑
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec4 ambient  = light.ambient  * vec4(texture(material.diffuse, TexCoord));
    vec4 diffuse  = light.diffuse  * diff * vec4(texture(material.diffuse, TexCoord)) * intensity;
    vec4 specular = light.specular * spec * vec4(texture(material.specular, TexCoord)) * intensity;

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	vec4 result = vec4(0,0,0,0);
	result += CalcDirLight(dirLight, norm, viewDir);
	result += CalcPointLight(pointLight, norm, FragPos, viewDir);
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = result;
}

