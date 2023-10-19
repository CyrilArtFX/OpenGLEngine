#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

#include <Rendering/shader.h>
#include <Rendering/texture.h>
#include <Rendering/vertexArray.h>
#include <Rendering/camera.h>

#include <Maths/Matrix4.h>
#include <Maths/Vector3.h>

#include <string>
#include <iostream>
#pragma once

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool initialize(int wndw_width = 1024, int wndw_height = 720, std::string wndw_name = "OpenGL Engine", bool wndw_capturemouse = true);
	void run();
	void close();



	//  functions redirected
	void windowResize(GLFWwindow* glWindow, int width, int height);
	void processMouse(GLFWwindow* glWindow, double xpos, double ypos);
	void processScroll(GLFWwindow* glWindow, double xoffset, double yoffset);

	void processInput(GLFWwindow* glWindow);

private:
	//  window
	Window window;

	//  time
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//  camera
	Camera camera;


	//  mouse
	bool firstMouse = true;
	float lastX = 0;
	float lastY = 0;


	//  will be put in a scene logic when I will do that
	


	//  will be implemented better after finishing 'lighting' part
	
};

