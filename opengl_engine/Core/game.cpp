#include "game.h"
#include <Assets/assetManager.h>
#include <Inputs/input.h>


Game::Game()
{
}


bool Game::initialize(int wndw_width, int wndw_height, std::string wndw_name, bool wndw_capturemouse)
{
	//  create window and initialize glfw
	window = std::make_unique<Window>(wndw_width, wndw_height, wndw_name, wndw_capturemouse);

	GLFWwindow* gl_window = window->getGLFWwindow();
	if (gl_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}


	glfwSetWindowUserPointer(gl_window, this);

	glfwSetFramebufferSizeCallback(gl_window, [](GLFWwindow* window, int width, int height)
		{
			auto self = static_cast<Game*>(glfwGetWindowUserPointer(window));
			self->windowResize(window, width, height);
		}
	); //  link window resize callback function

	glfwSetCursorPosCallback(gl_window, [](GLFWwindow* window, double xpos, double ypos)
		{
			auto self = static_cast<Game*>(glfwGetWindowUserPointer(window));
			self->processMouse(window, xpos, ypos);
		}
	); //  link mouse pos callback function

	glfwSetScrollCallback(gl_window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			auto self = static_cast<Game*>(glfwGetWindowUserPointer(window));
			self->processScroll(window, xoffset, yoffset);
		}
	); //  link mouse scroll callback function


	//  create renderer
	renderer = std::make_shared<Renderer>(Color{ 50, 75, 75, 255 }, *window);

	//  create freecam
	freecam = std::make_shared<Camera>(Vector3::zero);


	//  initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}


	//  initialize SDL Events
	if (SDL_Init(SDL_INIT_EVENTS) != 0)
	{
		std::cout << "Failed to initialize SDL Events" << std::endl;
		return false;
	}


	//  configure global OpenGL properties
	glEnable(GL_DEPTH_TEST);


	lastX = wndw_width / 2;
	lastY = wndw_height / 2;


	return true;
}


void Game::run()
{
	//  main loop
	while (!glfwWindowShouldClose(window->getGLFWwindow()))
	{
		//  time logic
		float current_frame = glfwGetTime();
		deltaTime = current_frame - lastFrame;
		lastFrame = current_frame;


		//  inputs part
		// -------------
		processInput(window->getGLFWwindow());


		if (!gamePaused)
		{
			if (scene) scene->update(deltaTime);
		}


		//  rendering part
		// ----------------

		renderer->draw();



		//  events and buffer swap
		glfwSwapBuffers(window->getGLFWwindow());
		glfwPollEvents();
	}


	unloadScene();
	AssetManager::DeleteObjects();
}


void Game::close()
{
	//  properly clear GLFW before closing app
	glfwTerminate();
}

void Game::loadScene(std::weak_ptr<Scene> scene_)
{
	scene = scene_.lock();
	scene->load(renderer);
}

void Game::unloadScene()
{
	if (scene) scene->unload();
}





void Game::processInput(GLFWwindow* glWindow)
{
	Input::UpdateKeys();

	if (Input::IsKeyPressed(SDL_SCANCODE_J))
	{
		std::cout << "test 1 2 1 2\n";
	}


	//  close window when escape is pressed
	if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glWindow, true);
	}


	

	//  pause/unpause the game when p is pressed
	if (glfwGetKey(glWindow, GLFW_KEY_P) == GLFW_PRESS && !pauseInptPrsd)
	{
		pauseInptPrsd = true;
		if (!gamePaused) pauseGame();
		else unpauseGame();
	}
	if (glfwGetKey(glWindow, GLFW_KEY_P) == GLFW_RELEASE)
	{
		pauseInptPrsd = false;
	}

	//  active/desactive the freecam mode when m is pressed
	if (glfwGetKey(glWindow, GLFW_KEY_SEMICOLON) == GLFW_PRESS && !freecamInptPrsd)
	{
		freecamInptPrsd = true;
		if (!freecamMode) enableFreecam();
		else disableFreecam();
	}
	if (glfwGetKey(glWindow, GLFW_KEY_SEMICOLON) == GLFW_RELEASE)
	{
		freecamInptPrsd = false;
	}


	if (!gamePaused)
	{
		if (scene) scene->processInputs(glWindow, deltaTime);
	}

	if (freecamMode)
	{
		//  move freecam
		if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
			freecam->freecamKeyboard(Camera_Movement::Forward, deltaTime);

		if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
			freecam->freecamKeyboard(Camera_Movement::Backward, deltaTime);

		if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
			freecam->freecamKeyboard(Camera_Movement::Left, deltaTime);

		if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
			freecam->freecamKeyboard(Camera_Movement::Right, deltaTime);

		if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
			freecam->freecamKeyboard(Camera_Movement::Up, deltaTime);

		if (glfwGetKey(glWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			freecam->freecamKeyboard(Camera_Movement::Down, deltaTime);
	}
}

void Game::pauseGame()
{
	gamePaused = true;
	std::cout << "Game paused.\n";
}

void Game::unpauseGame()
{
	gamePaused = false;
	if(freecamMode) disableFreecam();
	std::cout << "Game unpaused.\n";
}

void Game::enableFreecam()
{
	freecamMode = true;
	if (!gamePaused) pauseGame();
	std::cout << "Freecam mode enabled.\n";
	freecam->setPosition(scene->getCamera().lock()->getPosition());
	freecam->setRotation(scene->getCamera().lock()->getRotation());
	renderer->setCamera(freecam);
}

void Game::disableFreecam()
{
	freecamMode = false;
	std::cout << "Freecam mode disabled.\n";
	renderer->setCamera(scene->getCamera());
}


//  callback functions
void Game::windowResize(GLFWwindow* glWindow, int width, int height)
{
	glViewport(0, 0, width, height); //  resize OpenGL viewport when GLFW is resized
	window->changeSize(width, height);
}

void Game::processMouse(GLFWwindow* glWindow, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float x_offset = lastX - xpos;
	float y_offset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (!gamePaused)
	{
		if (scene) scene->processMouse(x_offset, y_offset);
	}

	if (freecamMode)
	{
		freecam->freecamMouseMovement(x_offset, y_offset);
	}
}

void Game::processScroll(GLFWwindow* glWindow, double xoffset, double yoffset)
{
	float scroll_offset = float(yoffset);

	if (!gamePaused)
	{
		if (scene) scene->processScroll(scroll_offset);
	}

	if (freecamMode)
	{
		freecam->freecamMouseScroll(scroll_offset);
	}
}
