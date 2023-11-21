#include "window.h"

Window::Window(int width, int height, std::string windowName, bool mouseCaptured)
{
	//  initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	windowWidth = width;
	windowHeight = height;

	//  create GLFW window
	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);

	glfwMakeContextCurrent(window);

	//  capture mouse
	if (mouseCaptured)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Window::changeSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}
