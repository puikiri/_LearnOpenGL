#version 330 core
in vec2 TexCoord;
in vec3 Normal; // ������(����)
in vec3 FragPos; // ����λ�ã����磩
in vec3 LightPos; // �ƹ�λ�ã����磩
in vec3 ViewPos;  // ���λ��(����)

out vec4 FragColor;

uniform sampler2D baseTexture;
uniform vec4 objectColor; // ������ɫ
uniform vec4 lightColor; // �ƹ���ɫ

struct Material { // ����
    sampler2D frameTex;
    vec3 ambientStrength; // ambient���������������ڻ���������������巴�����ʲô��ɫ��ͨ�����Ǻ�������ɫ��ͬ����ɫ
    vec3 diffuseStrength; // diffuse����������������������������������ɫ�����ͻ�������һ������������ɫҲҪ����Ϊ������Ҫ��������ɫ��
    vec3 specularStrength; // specular�����������õ��Ǿ�����ն��������ɫӰ�죨�����������ܷ���һ�������ض��ľ���߹���ɫ����
    float shininess; // shininessӰ�쾵��߹��ɢ��/�뾶��
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
	// Phong // ģ�⻷������
	///* �ƹ�
	float r = min(max(lightColor.x, 0.1), 1);
	float g = min(max(lightColor.y, 0.1), 1);
	float b = min(max(lightColor.z, 0.1), 1);
	float a = min(max(lightColor.w, 0.1), 1);
	vec4 tLightColor = vec4(r, g, b, a);

	/// * ������
    vec4 ambient = tLightColor * vec4(material.ambientStrength, 1.0);

	///* �������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = tLightColor * diff * vec4(material.diffuseStrength, 1.0f);

	///* �߹�
	vec3 viewDir = normalize(ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = tLightColor * vec4(texture(material.frameTex, TexCoord)) * vec4(material.specularStrength, 1.0f) * spec;

    vec4 result = (ambient + diffuse + specular) * objectColor;

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * result;
}

