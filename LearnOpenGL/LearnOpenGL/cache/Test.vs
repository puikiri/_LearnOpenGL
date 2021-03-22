#version 330 core
layout (location = 0) in vec3 aPos; 
/*
 location = x : xƫ��λ��������glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer); ��1,2��β���й�ϵ��
 �ٸ����ӣ�
 ??.vs
 ...
 layout (location = 0) ...; 
 layout (location = 1) ...; 
 ...
 ��ôʹ��ʱ��
 glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0); ���Ƕ�Ӧlocation = 0�ģ�
						�˴���ֻʹ���� stride(7)��ǰ�벿��3����
 glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float))); ���Ƕ�Ӧlocation = 1�ģ�
						�˴��� ʹ���� stride(7)�ĺ�벿��3�����ʴ˴� �� ��ָ����Ҫƫ��location = 0ʱʹ�õ�����
						����һ�ε� index*size*sizeof(type) ��Ϊƫ�ƣ��� 1*3*sizeof(float)��¥�ϵ�0Ҳ�������Ϊ 0*0*sizeof(float)��
�˴��Ϳ��԰�location = 0��������(��)���εĶ��㣬location = 1��������ɫ/͸���ȵȵ�������Ҫ�õ�������
 */
out vec4 vertexColor;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = vec4(0.5, 0.4, 0.3, 1.0);
}
