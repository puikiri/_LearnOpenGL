#version 330 core
in vec2 TexCoord;
in vec3 Normal; // ������(����)
in vec3 FragPos; // ����λ�ã����磩

out vec4 FragColor;

uniform vec3 viewPos; // ���λ��

struct Material { // ����
    sampler2D diffuse;
    sampler2D specular;
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
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // �ϲ����
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
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // ˥��
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * (distance * distance));    
    // �ϲ����
    vec4 ambient  = light.ambient  * vec4(texture(material.diffuse, TexCoord));
    vec4 diffuse  = light.diffuse  * diff * vec4(texture(material.diffuse, TexCoord));
    vec4 specular = light.specular * spec * vec4(texture(material.specular, TexCoord));

    return attenuation * (ambient + diffuse + specular);
}

struct SpotLight {
	// �۹�
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
	// �۹�ļ���
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction)); 
	// �۹���Ȧ�Ử
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
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

