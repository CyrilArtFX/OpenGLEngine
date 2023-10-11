#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
	Window() = default;

	//  initialize glfw and create a glfw window
	Window(int width, int height, const char* windowName, bool mouseCaptured);

	GLFWwindow* getGLFWwindow() { return window; }

	int getWidth() { return window_width; }
	int getHeigth() { return window_height; }

	void changeSize(int width, int height);

private:
	GLFWwindow* window;
	int window_width;
	int window_height;
};

