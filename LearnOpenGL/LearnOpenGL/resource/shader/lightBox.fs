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

struct Material { // 材质
    sampler2D frameTex;
    vec3 ambientStrength; // ambient材质向量定义了在环境光照下这个物体反射得是什么颜色，通常这是和物体颜色相同的颜色
    vec3 diffuseStrength; // diffuse材质向量定义了在漫反射光照下物体的颜色。（和环境光照一样）漫反射颜色也要设置为我们需要的物体颜色。
    vec3 specularStrength; // specular材质向量设置的是镜面光照对物体的颜色影响（或者甚至可能反射一个物体特定的镜面高光颜色）。
    float shininess; // shininess影响镜面高光的散射/半径。
}; 

/*
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
*/

uniform Material material;

void main()
{
	// Phong // 模拟环境光照
	///* 灯光
	float r = min(max(lightColor.x, 0.1), 1);
	float g = min(max(lightColor.y, 0.1), 1);
	float b = min(max(lightColor.z, 0.1), 1);
	float a = min(max(lightColor.w, 0.1), 1);
	vec4 tLightColor = vec4(r, g, b, a);

	/// * 环境光
    vec4 ambient = tLightColor * vec4(material.ambientStrength, 1.0);

	///* 漫反射光
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = tLightColor * diff * vec4(material.diffuseStrength, 1.0f);

	///* 高光
	vec3 viewDir = normalize(ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = tLightColor * vec4(texture(material.frameTex, TexCoord)) * vec4(material.specularStrength, 1.0f) * spec;

    vec4 result = (ambient + diffuse + specular) * objectColor;

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * result;
}

