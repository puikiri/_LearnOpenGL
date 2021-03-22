#version 330 core
layout (location = 0) in vec3 aPos; 
/*
 location = x : x偏移位置量。和glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer); 的1,2，尾参有关系。
 举个例子：
 ??.vs
 ...
 layout (location = 0) ...; 
 layout (location = 1) ...; 
 ...
 那么使用时：
 glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0); 这是对应location = 0的，
						此处是只使用了 stride(7)的前半部分3个，
 glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float))); 这是对应location = 1的，
						此处是 使用了 stride(7)的后半部分3个，故此处 ↑ 的指针需要偏移location = 0时使用的量，
						即上一次的 index*size*sizeof(type) 作为偏移，即 1*3*sizeof(float)。楼上的0也可以理解为 0*0*sizeof(float)；
此处就可以把location = 0当成是三(多)角形的顶点，location = 1当成是颜色/透明度等等其他需要用到的属性
 */
out vec4 vertexColor;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = vec4(0.5, 0.4, 0.3, 1.0);
}
