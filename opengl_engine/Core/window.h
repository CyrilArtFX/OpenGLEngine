#pragma once

#include <GLFW/glfw3.h>
#include <string>

//  default values
const int WNDW_WIDTH = 1024;
const int WNDW_HEIGHT = 720;
const std::string WNDW_NAME = "OpenGL Engine";
const bool WNDW_CAPT_MOUSE = true;

class Window
{
public:
	//  initialize glfw and create a glfw window
	Window(int width = WNDW_WIDTH, int height = WNDW_HEIGHT, std::string windowName = WNDW_NAME, bool mouseCaptured = WNDW_CAPT_MOUSE);
	Window() = delete;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	GLFWwindow* getGLFWwindow() { return window; }

	int getWidth() const { return windowWidth; }
	int getHeigth() const { return windowHeight; }

	void changeSize(int width, int height);

private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
};

