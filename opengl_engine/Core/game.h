#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "window.h"
#include <Rendering/renderer.h>
#include <Rendering/texture.h>

#include <Maths/matrix4.h>
#include <Maths/vector3.h>

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

	void loadScene(std::weak_ptr<Scene> scene_);
	void unloadScene();



	//  functions redirected
	void windowResize(GLFWwindow* glWindow, int width, int height);
	void processMouse(GLFWwindow* glWindow, double xpos, double ypos);
	void processScroll(GLFWwindow* glWindow, double xoffset, double yoffset);

	void processInput(GLFWwindow* glWindow);

private:
	//  scene
	std::shared_ptr<Scene> scene;

	//  window
	std::unique_ptr<Window> window;

	//  renderer
	std::shared_ptr<Renderer> renderer;

	//  time
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//  pause and freecam
	bool gamePaused{ false };
	bool freecamMode{ false };
	bool pauseInptPrsd{ false };
	bool freecamInptPrsd{ false };
	void pauseGame();
	void unpauseGame();
	void enableFreecam();
	void disableFreecam();


	//  mouse
	bool firstMouse = true;
	float lastX = 0;
	float lastY = 0;
};

