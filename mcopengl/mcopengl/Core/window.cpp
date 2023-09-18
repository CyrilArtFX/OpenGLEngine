#include "window.h"

Window::Window(int width, int height, const char* windowName, bool mouseCaptured)
{
	//  initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//  create GLFW window
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);

	glfwMakeContextCurrent(window);

	//  capture mouse
	if (mouseCaptured)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}
