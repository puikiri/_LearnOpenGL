#version 330 core
in vec2 TexCoord;
in vec3 Normal; // ������(����)
in vec3 FragPos; // ����λ�ã����磩

out vec4 FragColor;

uniform sampler2D baseTexture;
uniform vec3 viewPos; // ���λ��

struct Material { // ����
    sampler2D frameTex;
    vec4 ambient; // ambient���������������ڻ���������������巴�����ʲô��ɫ��ͨ�����Ǻ�������ɫ��ͬ����ɫ
    vec4 diffuse; // diffuse����������������������������������ɫ�����ͻ�������һ������������ɫҲҪ����Ϊ������Ҫ��������ɫ��
    vec4 specular; // specular�����������õ��Ǿ�����ն��������ɫӰ�죨�����������ܷ���һ�������ض��ľ���߹���ɫ����
    float shininess; // shininessӰ�쾵��߹��ɢ��/�뾶��
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
	// Phong // ģ�⻷������

	/// * ������
    vec4 ambient = light.ambient * material.ambient;
	/*
	�˴��Ĺ�����Ϣ����������ã� ����materialһ������
	*/
	///* �������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = light.diffuse * diff * material.diffuse;

	///* �߹�
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = light.specular * vec4(texture(material.frameTex, TexCoord)) * material.specular * spec;

    vec4 result = ambient + diffuse + specular;

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * result;

	//FragColor = result;
}

