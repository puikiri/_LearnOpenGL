#ifndef DEFINE_H
#define DEFINE_H

/* system */
#define glfwClearColor 0.0f, 0.0f, 0.0f, 1.0f
#define winSizeW 1080
#define winSizeH 720
#define viewFov 60.f
#define viewZNear 0.1f
#define viewZFar 300.f
#define glfwVerMajor 3
#define glfwVerMinor 3

/* method */
#define Assert(flag, str) if(!flag){ printf(str); assert(false);}





#endif