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

uniform sampler2D ourTexture;
/*
采样器：接收纹理的。
sampler1D/sampler2D/sampler3D

使用glUniform1i，可以给采样器分配一个位置值，这样的话就能够在一个片段着色器中设置多个纹理。一个纹理的位置值通常称为一个纹理单元(Texture Unit)。一个纹理的默认纹理单元是0，它是默认的激活纹理单元。
OpenGL至少保证有16个纹理单元供你使用，也就是说你可以激活从GL_TEXTURE0到GL_TEXTRUE15。它们都是按顺序定义的，所以我们也可以通过GL_TEXTURE0 + 8的方式获得GL_TEXTURE8，这在当我们需要循环一些纹理单元的时候会很有用。
*/

void main()
{
	FragColor = vertexColor;
}

