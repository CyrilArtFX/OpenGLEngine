#include "game.h"


Game::Game()
{
}


bool Game::initialize(int wndw_width, int wndw_height, std::string wndw_name, bool wndw_capturemouse)
{
	//  create window and initialize glfw
	window = std::make_unique<Window>(wndw_width, wndw_height, wndw_name, wndw_capturemouse);

	GLFWwindow* glWindow = window->getGLFWwindow();
	if (glWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}


	glfwSetWindowUserPointer(glWindow, this);

	glfwSetFramebufferSizeCallback(glWindow, [](GLFWwindow* window, int width, int height)
		{
			auto self = static_cast<Game*>(glfwGetWindowUserPointer(window));
			self->windowResize(window, width, height);
		}
	); //  link window resize callback function

	glfwSetCursorPosCallback(glWindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			auto self = static_cast<Game*>(glfwGetWindowUserPointer(window));
			self->processMouse(window, xpos, ypos);
		}
	); //  link mouse pos callback function

	glfwSetScrollCallback(glWindow, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			auto self = static_cast<Game*>(glfwGetWindowUserPointer(window));
			self->processScroll(window, xoffset, yoffset);
		}
	); //  link mouse scroll callback function


	//  create renderer
	renderer = std::make_shared<Renderer>(Color{ 50, 75, 75, 255 }, *window);


	//  initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
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
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		//  inputs part
		// -------------
		processInput(window->getGLFWwindow());


		if (scene) scene->update(deltaTime);


		//  rendering part
		// ----------------

		renderer->draw();



		//  events and buffer swap
		glfwSwapBuffers(window->getGLFWwindow());
		glfwPollEvents();
	}


	unloadScene();
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
	//  close window when escape is pressed
	if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glWindow, true);
	}

	if (scene) scene->processInputs(glWindow, deltaTime);
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

	float xoffset = lastX - xpos;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (scene) scene->processMouse(xoffset, yoffset);
}

void Game::processScroll(GLFWwindow* glWindow, double xoffset, double yoffset)
{
	float scrolloffset = float(yoffset);

	if (scene) scene->processScroll(scrolloffset);
}
