#version 330 core
in vec4 vertexColor;
/*
���ԺͶ�����ɫ���ɶԣ�������ɫ����out�Ϳ��Զ�Ӧ�������in(���ƺ�����Ҫ����)�����ʹ��uniform����û˵��
���û�ж��ϵĻ���ֻ�ܿ�gl�����ˡ�
*/
uniform vec4 ourColor; 
/*
uniform �������ǿ�����OpenGL����������趨/�ı�ı�����
��Ҫ�����˲��ã�����µġ�
������gl��������glGetUniformLocation(shaderProgram, uniform��������)��ö�Ӧ��id(location)��
Ȼ��ͨ��glUniform4f(�����ȡ��id(location), ....)����ֵ
*/
out vec4 FragColor;
void main()
{
	FragColor = vertexColor;
}

