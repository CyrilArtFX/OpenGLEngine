#include "engine.h"
#include <Assets/assetManager.h>
#include <Inputs/input.h>


Engine::Engine()
{
}


bool Engine::initialize(int wndw_width, int wndw_height, std::string wndw_name, bool wndw_capturemouse)
{
	//  create window and initialize glfw
	window.createWindow(wndw_width, wndw_height, wndw_name, wndw_capturemouse);

	GLFWwindow* gl_window = window.getGLFWwindow();
	if (gl_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}


	glfwSetWindowUserPointer(gl_window, this);

	glfwSetFramebufferSizeCallback(gl_window, [](GLFWwindow* window, int width, int height)
		{
			auto self = static_cast<Engine*>(glfwGetWindowUserPointer(window));
			self->windowResize(window, width, height);
		}
	); //  link window resize callback function

	glfwSetCursorPosCallback(gl_window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Input::ProcessMouse(window, xpos, ypos);
		}
	); //  link mouse pos callback function

	glfwSetScrollCallback(gl_window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			Input::ProcessScroll(window, xoffset, yoffset);
		}
	); //  link mouse scroll callback function

	glfwSetKeyCallback(gl_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input::ProcessKeyboard(window, key, scancode, action, mods);
		}
	); //  link keyboard callback function

	glfwSetMouseButtonCallback(gl_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			Input::ProcessMouseButton(window, button, action, mods);
		}
	); //  link mouse button callback function


	//  create renderer
	renderer.createRenderer(Color::black, Vector2Int{ window.getWidth(), window.getHeigth() });

	//  set freecam values
	freecam.setSpeed(4.0f);


	//  initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}


	//  initialize input system
	Input::Initialize();


	//  configure global OpenGL properties
	glEnable(GL_DEPTH_TEST);


	return true;
}


void Engine::run()
{
	//  main loop
	while (!glfwWindowShouldClose(window.getGLFWwindow()))
	{
		//  time logic part
		// -----------------
		float current_frame = glfwGetTime();
		deltaTime = current_frame - lastFrame;
		lastFrame = current_frame;


		//  inputs update part
		// -------------
		Input::UpdateInputSystem(); //  update the keys that were registered during the last frame


		//  update part
		// -------------
		engineUpdate(window.getGLFWwindow());

		if (!gamePaused)
		{
			if (game)
			{
				game->updateGame(deltaTime);
				game->updateScene(deltaTime);
			}
		}


		//  rendering part
		// ----------------
		renderer.draw();


		//  events and buffer swap part
		// -----------------------------
		glfwSwapBuffers(window.getGLFWwindow());
		glfwPollEvents();
	}

	//  close engine
	unloadGame();
	AssetManager::DeleteObjects();
}


void Engine::close()
{
	//  properly clear GLFW before closing app
	glfwTerminate();
}

void Engine::loadGame(std::weak_ptr<Game> game_)
{
	game = game_.lock();
	game->load(&renderer);
}

void Engine::unloadGame()
{
	if (game) game->unload();
}


void Engine::engineUpdate(GLFWwindow* glWindow)
{
	//  close window when escape is pressed
	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glWindow, true);
	}

	//  pause and freecam are useless if there is no active game or scene
	if (!game || !game->hasActiveScene()) return;

	//  pause/unpause the game when p is pressed
	if (Input::IsKeyPressed(GLFW_KEY_P))
	{
		if (!gamePaused) pauseGame();
		else unpauseGame();
	}

	//  active/desactive the freecam mode when m is pressed
	if (Input::IsKeyPressed(GLFW_KEY_SEMICOLON))
	{
		if (!freecamMode) enableFreecam();
		else disableFreecam();
	}

	if (freecamMode)
	{
		//  move freecam
		if (Input::IsKeyDown(GLFW_KEY_W))
			freecam.freecamKeyboard(Camera_Movement::Forward, deltaTime);

		if (Input::IsKeyDown(GLFW_KEY_S))
			freecam.freecamKeyboard(Camera_Movement::Backward, deltaTime);

		if (Input::IsKeyDown(GLFW_KEY_A))
			freecam.freecamKeyboard(Camera_Movement::Left, deltaTime);

		if (Input::IsKeyDown(GLFW_KEY_D))
			freecam.freecamKeyboard(Camera_Movement::Right, deltaTime);

		if (Input::IsKeyDown(GLFW_KEY_SPACE))
			freecam.freecamKeyboard(Camera_Movement::Up, deltaTime);

		if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
			freecam.freecamKeyboard(Camera_Movement::Down, deltaTime);

		Vector2 mouse_delta = Input::GetMouseDelta();
		freecam.freecamMouseMovement(mouse_delta.x, mouse_delta.y);

		freecam.freecamMouseScroll(Input::GetScrollOffset());
	}
}


void Engine::pauseGame()
{
	gamePaused = true;
	std::cout << "Game paused.\n";
}

void Engine::unpauseGame()
{
	gamePaused = false;
	if (freecamMode) disableFreecam();
	std::cout << "Game unpaused.\n";
}

void Engine::enableFreecam()
{
	freecamMode = true;
	if (!gamePaused) pauseGame();
	std::cout << "Freecam mode enabled.\n";
	freecam.copyCameraTransform(game->getActiveCamera());
	renderer.setCamera(&freecam);
}

void Engine::disableFreecam()
{
	freecamMode = false;
	std::cout << "Freecam mode disabled.\n";
	renderer.setCamera(&game->getActiveCamera());
}


//  window resize callback functions
void Engine::windowResize(GLFWwindow* glWindow, int width, int height)
{
	glViewport(0, 0, width, height); //  resize OpenGL viewport when GLFW is resized
	window.changeSize(width, height);
	renderer.setWindowSize(Vector2Int{ window.getWidth(), window.getHeigth() });
}
