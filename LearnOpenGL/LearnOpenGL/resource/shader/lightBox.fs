#version 330 core
in vec2 TexCoord;
in vec3 Normal; // 法向量(世界)
in vec3 FragPos; // 顶点位置（世界）
in vec3 LightPos; // 灯光位置（世界）
in vec3 ViewPos;  // 相机位置(世界)

out vec4 FragColor;

uniform sampler2D baseTexture;
uniform vec4 objectColor; // 物体颜色
uniform vec4 lightColor; // 灯光颜色

void main()
{
	// Phong 
	// 模拟环境光照
    float ambientStrength = 0.1; // 环境光系数
	float specularStrength = 0.5; // 高光系数
	float specularPow = 32; // 高光反光值
	///* 灯光
	float r = min(max(lightColor.x, ambientStrength), 1);
	float g = min(max(lightColor.y, ambientStrength), 1);
	float b = min(max(lightColor.z, ambientStrength), 1);
	float a = min(max(lightColor.w, ambientStrength), 1);
	vec4 tLightColor = vec4(r, g, b, a);
    vec4 ambient = ambientStrength * tLightColor;

	///* 环境光
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * tLightColor;

	///* 高光
	vec3 viewDir = normalize(ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularPow);
	vec4 specular = specularStrength * spec * lightColor;

    vec4 result = (ambient + diffuse + specular) * objectColor;

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * result;
}

