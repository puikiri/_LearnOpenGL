#version 330 core
in vec2 TexCoord;
in vec3 Normal; // 法向量(世界)
in vec3 FragPos; // 顶点位置（世界）

out vec4 FragColor;

uniform vec3 viewPos; // 相机位置

struct Material { // 材质
    sampler2D diffTex;
    sampler2D frameTex;
    //vec4 ambient; // ambient材质向量定义了在环境光照下这个物体反射得是什么颜色，通常这是和物体颜色相同的颜色
    //vec4 diffuse; // diffuse材质向量定义了在漫反射光照下物体的颜色。（和环境光照一样）漫反射颜色也要设置为我们需要的物体颜色。
    //vec4 specular; // specular材质向量设置的是镜面光照对物体的颜色影响（或者甚至可能反射一个物体特定的镜面高光颜色）。
    float shininess; // shininess影响镜面高光的散射/半径。
}; 

struct Light {
	vec3 lightPos;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

uniform Material material;
uniform Light light;

void main()
{
	// Phong // 模拟环境光照
	/// * 环境光
    vec4 ambient = vec4(texture(material.diffTex, TexCoord)) * light.ambient;
	///* 漫反射光
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = vec4(texture(material.diffTex, TexCoord)) * light.diffuse * diff;

	///* 高光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = light.specular * vec4(texture(material.frameTex, TexCoord)) * spec;

	FragColor = ambient + diffuse + specular;
}

