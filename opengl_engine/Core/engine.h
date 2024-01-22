#pragma once

#include "game.h"
#include "window.h"
#include <Rendering/renderer.h>
#include <Rendering/camera.h>
#include <Rendering/texture.h>

#include <Maths/matrix4.h>
#include <Maths/vector3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Engine
{
public:
	Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	bool initialize(int wndw_width = 1024, int wndw_height = 720, std::string wndw_name = "OpenGL Engine", bool wndw_capturemouse = true);
	void run();
	void close();

	void loadGame(std::weak_ptr<Game> game_);
	void unloadGame();

	void engineUpdate(GLFWwindow* glWindow);

	//  window resize function redirected
	void windowResize(GLFWwindow* glWindow, int width, int height);

private:
	//  game
	std::shared_ptr<Game> game;

	//  window
	Window window;

	//  renderer
	Renderer renderer;

	//  freecam
	Camera freecam;

	//  time
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//  pause and freecam
	bool gamePaused{ false };
	bool freecamMode{ false };
	bool debugViewMode{ false };
	void pauseGame();
	void unpauseGame();
	void enableFreecam();
	void disableFreecam();
	void enableDebugView();
	void disableDebugView();
};
