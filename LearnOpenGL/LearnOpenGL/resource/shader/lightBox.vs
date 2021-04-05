#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal; // ����λ�ã��ֲ���
layout (location = 2) in vec2 inTexCoord; // ����λ��(s,t)

out vec2 TexCoord;
out vec3 Normal; // ������(����)
out vec3 FragPos;  // ����λ��(����)
out vec3 LightPos;  // �ƹ�λ��(����)
out vec3 ViewPos;  // ���λ��(����)

uniform mat4 transform; // all�任����
uniform mat4 modelMat; // model�任����
uniform vec3 lightPos; // �ƹ�λ�ã��ֲ���
uniform vec3 viewPos; // ���λ�ã��ֲ���

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
    TexCoord = inTexCoord;
	Normal = mat3(transpose(inverse(modelMat))) * normal; // ��������Ҫ ʹ��inverse��transpose�����Լ����ɷ��߾��� �����⴦������ٶ�
	//Normal = normal;
	FragPos = vec3(modelMat * vec4(pos, 1.0));
	LightPos = vec3(modelMat * vec4(lightPos, 1.0));
	ViewPos = vec3(modelMat * vec4(viewPos, 1.0));
}
