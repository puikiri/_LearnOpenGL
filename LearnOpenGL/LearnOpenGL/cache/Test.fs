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

uniform sampler2D ourTexture;
/*
����������������ġ�
sampler1D/sampler2D/sampler3D

ʹ��glUniform1i�����Ը�����������һ��λ��ֵ�������Ļ����ܹ���һ��Ƭ����ɫ�������ö������һ�������λ��ֵͨ����Ϊһ������Ԫ(Texture Unit)��һ�������Ĭ������Ԫ��0������Ĭ�ϵļ�������Ԫ��
OpenGL���ٱ�֤��16������Ԫ����ʹ�ã�Ҳ����˵����Լ����GL_TEXTURE0��GL_TEXTRUE15�����Ƕ��ǰ�˳����ģ���������Ҳ����ͨ��GL_TEXTURE0 + 8�ķ�ʽ���GL_TEXTURE8�����ڵ�������Ҫѭ��һЩ����Ԫ��ʱ�������á�
*/

void main()
{
	FragColor = vertexColor;
}

