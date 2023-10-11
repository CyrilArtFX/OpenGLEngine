#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
	//  initialize glfw and create a glfw window
	Window(int width, int height, const char* windowName, bool mouseCaptured);

	GLFWwindow* getGLFWwindow() { return window; }

private:
	GLFWwindow* window;
};

