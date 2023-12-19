#pragma once

#include "scene.h"
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

	void loadScene(std::weak_ptr<Scene> scene_);
	void unloadScene();

	void engineUpdate(GLFWwindow* glWindow);

	//  window resize function redirected
	void windowResize(GLFWwindow* glWindow, int width, int height);

private:
	//  scene
	std::shared_ptr<Scene> scene;

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
	void pauseGame();
	void unpauseGame();
	void enableFreecam();
	void disableFreecam();
};
