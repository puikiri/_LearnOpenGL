#version 330 core
in vec4 vertexColor;
/*
可以和顶点着色器成对，顶点着色器的out就可以对应到这里的in(名称和类型要对上)。如果使用uniform当我没说。
如果没有对上的话，只能靠gl处理了。
*/
uniform vec4 ourColor; 
/*
uniform 声明的是可以在OpenGL程序代码中设定/改变的变量。
不要声明了不用，会出事的。
可以在gl程序中用glGetUniformLocation(shaderProgram, uniform的属性名)获得对应的id(location)，
然后通过glUniform4f(上面获取的id(location), ....)设置值
*/
out vec4 FragColor;
void main()
{
	FragColor = vertexColor;
}

