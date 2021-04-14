#version 330 core
in vec2 TexCoord;
in vec3 Normal; // ������(����)
in vec3 FragPos; // ����λ�ã����磩

out vec4 FragColor;

uniform vec3 viewPos; // ���λ��

struct Material { // ����
    sampler2D diffTex;
    sampler2D frameTex;
    //vec4 ambient; // ambient���������������ڻ���������������巴�����ʲô��ɫ��ͨ�����Ǻ�������ɫ��ͬ����ɫ
    //vec4 diffuse; // diffuse����������������������������������ɫ�����ͻ�������һ������������ɫҲҪ����Ϊ������Ҫ��������ɫ��
    //vec4 specular; // specular�����������õ��Ǿ�����ն��������ɫӰ�죨�����������ܷ���һ�������ض��ľ���߹���ɫ����
    float shininess; // shininessӰ�쾵��߹��ɢ��/�뾶��
}; 

struct Light {
	// ������ԣ���¥��
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

	// �����
    vec3 direction; 
	// ���
	vec3 lightPos;
    float constant;
    float linear;
    float quadratic;
	// �۹�
	vec3 cameralightPos;
    vec3 cameraDirection;
    float cutOff;
	float outerCutOff;
};

uniform Material material;
uniform Light light;

void main()
{
	// ����˥������
	float distance  = length(light.lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * (distance * distance));

	// �۹�ļ���
	vec3 clightDir = normalize(light.cameralightPos - FragPos);
	float theta = dot(clightDir, normalize(-light.cameraDirection)); 
	// �۹���Ȧ�Ử
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	
	// Phong // ģ�⻷������
	/// * ������
    vec4 ambient = vec4(texture(material.diffTex, TexCoord)) * light.ambient;
	///* �������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos); // ���
	//vec3 lightDir = normalize(-light.direction); // ƽ�й�/�����
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = vec4(texture(material.diffTex, TexCoord)) * light.diffuse * diff * intensity;

	///* �߹�
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = light.specular * vec4(texture(material.frameTex, TexCoord)) * spec * intensity;

	FragColor = attenuation * (ambient + diffuse + specular);
}

