#include "engine.h"
#include <Assets/assetManager.h>
#include <Assets/defaultAssets.h>
#include <Assets/assetsIDs.h>
#include <Inputs/input.h>
#include <ServiceLocator/locator.h>
#include <Physics/physicsManager.h>
#include <GameplayStatics/gameplayStatics.h>

#include <Maths/vector4.h>


Engine::Engine()
{
}


bool Engine::initialize(int wndw_width, int wndw_height, std::string wndw_name, bool wndw_capturemouse)
{
	std::cout << "Initializing...\n\n\n";

	std::cout << "==================================================" << std::endl;
	std::cout << "   ____            _____             _            " << std::endl;
	std::cout << "  / ___|   _      | ____|_ __   __ _(_)_ __   ___ " << std::endl;
	std::cout << " | |  | | | |_____|  _| | '_ \\ / _` | | '_ \\ / _ \\ " << std::endl;
	std::cout << " | |__| |_| |_____| |___| | | | (_| | | | | |  __/" << std::endl;
	std::cout << "  \\____\\__, |     |_____|_| |_|\\__, |_|_| |_|\\___|" << std::endl;
	std::cout << "       |___/                   |___/              " << std::endl;
	std::cout << "==================================================" << std::endl << std::endl << std::endl;


	//  create window and initialize glfw
	std::cout << "Initializing window...";
	window.createWindow(wndw_width, wndw_height, wndw_name, wndw_capturemouse);

	GLFWwindow* gl_window = window.getGLFWwindow();
	if (gl_window == NULL)
	{
		std::cout << std::endl << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	std::cout << " Done.\n";


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


	//  initialize service locator
	std::cout << "Initializing service locator...";
	Locator::initialize();
	std::cout << " Done.\n";


	//  create renderer
	std::cout << "Initializing renderer...";
	renderer = new RendererOpenGL();
	Locator::provideRenderer(renderer);
	renderer->initializeRenderer(Color::black, Vector2Int{ window.getWidth(), window.getHeigth() });
	std::cout << " Done.\n";


	//  set freecam values
	freecam.setSpeed(4.0f);


	//  initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << std::endl << "Failed to initialize GLAD" << std::endl;
		return false;
	}


	//  initialize input system
	std::cout << "Initializing inputs...";
	Input::Initialize();
	std::cout << " Done.\n";

	//  initialize physics
	std::cout << "Initializing physics...";
	Physics& physics = Locator::providePhysics(new PhysicsManager());
	physics.InitialisePhysics();
	std::cout << " Done.\n";

	//  initialize audio manager
	std::cout << "Initializing audio...";
	audio = new AudioManager();
	Locator::provideAudio(audio);
	audio->Initialize(100.0f);
	std::cout << " Done.\n";


	//  load "null" assets of AssetManager
	std::cout << "Initializing asset manager...";
	AssetManager::LoadNullAssets();

	//  initialize assets IDs
	AssetsIDs::InitializeAssetIDs();

	//  load debug assets
	DefaultAssets::LoadDebugAssets();
	std::cout << " Done.\n";


	//  configure global OpenGL properties
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	std::cout << "\nEngine initialization: " << glfwGetTime() << " seconds.\n";

	std::cout << "\nCy-Engine is ready to run.\n\n\n";


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
		// --------------------
		Input::UpdateInputSystem(); //  update the keys that were registered during the last frame


		//  update part
		// -------------
		engineUpdate(window.getGLFWwindow());


		if (!gamePaused || (gamePaused && oneFrame))
		{
			Locator::getPhysics().UpdatePhysics(deltaTime);

			if (game)
			{
				game->updateGame(deltaTime);
				game->updateScene(deltaTime);
			}

			oneFrame = false;
		}


		//  rendering part
		// ----------------
		renderer->draw();


		//  TEXT RENDERING TEMPORARY
		RenderText(AssetManager::GetShader("text_render"), "Hello World!", -window.getWidth() / 2.0f + 20.0f, window.getHeigth() / 2.0f - 60.0f, 0.5f, Color::white);


		//  audio part
		// ------------
		const Camera& current_cam = renderer->GetCamera();
		audio->UpdateListener(current_cam.getPosition(), current_cam.getUp(), current_cam.getForward());
		audio->Update();


		//  events and buffer swap part
		// -----------------------------
		glfwSwapBuffers(window.getGLFWwindow());
		glfwPollEvents();
	}

	//  close engine
	unloadGame();
	audio->Quit();
}


void Engine::close()
{
	//  properly clear GLFW before closing app
	glfwTerminate();
}

void Engine::loadGame(std::weak_ptr<Game> game_)
{
	game = game_.lock();
	GameplayStatics::SetCurrentGame(game.get());
	game->load();
}

void Engine::unloadGame()
{
	if (game) game->unload();
	GameplayStatics::SetCurrentGame(nullptr);
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

	//  make the engine run only one frame when o is pressed
	if (Input::IsKeyPressed(GLFW_KEY_O))
	{
		advanceOneFrame();
	}

	//  active/desactive the freecam mode when m is pressed
	if (Input::IsKeyPressed(GLFW_KEY_SEMICOLON))
	{
		if (!freecamMode) enableFreecam();
		else disableFreecam();
	}

	//  active/desactive the debug view mode when k is pressed
	if (Input::IsKeyPressed(GLFW_KEY_K))
	{
		if (!debugViewMode) enableDebugView();
		else disableDebugView();
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

		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
			freecam.setSpeed(10.0f);

		if (Input::IsKeyReleased(GLFW_MOUSE_BUTTON_RIGHT))
			freecam.setSpeed(4.0f);

		Vector2 mouse_delta = Input::GetMouseDelta();
		freecam.freecamMouseMovement(mouse_delta.x, mouse_delta.y);

		freecam.freecamMouseScroll(Input::GetScrollOffset());
	}
}


void Engine::pauseGame()
{
	gamePaused = true;
	audio->PauseAll();
	std::cout << "Game paused.\n";
}

void Engine::unpauseGame()
{
	gamePaused = false;
	audio->ResumeAll();
	if (freecamMode) disableFreecam();
	std::cout << "Game unpaused.\n";
}

void Engine::advanceOneFrame()
{
	if (!gamePaused) pauseGame();
	else
	{
		std::cout << "Advance one frame.\n";
		oneFrame = true;
	}
}

void Engine::enableFreecam()
{
	freecamMode = true;
	if (!gamePaused) pauseGame();
	std::cout << "Freecam mode enabled.\n";
	freecam.copyCameraTransform(game->getActiveCamera());
	renderer->SetCamera(&freecam);
	freecam.setSpeed(4.0f);
}

void Engine::disableFreecam()
{
	freecamMode = false;
	std::cout << "Freecam mode disabled.\n";
	renderer->SetCamera(&game->getActiveCamera());
}

void Engine::enableDebugView()
{
	debugViewMode = true;
	std::cout << "Debug view mode enabled.\n";
	renderer->drawDebugMode = true;
}

void Engine::disableDebugView()
{
	debugViewMode = false;
	std::cout << "Debug view mode disabled.\n";
	renderer->drawDebugMode = false;
}


//  window resize callback functions
void Engine::windowResize(GLFWwindow* glWindow, int width, int height)
{
	glViewport(0, 0, width, height); //  resize OpenGL viewport when GLFW is resized
	window.changeSize(width, height);
	renderer->setWindowSize(Vector2Int{ window.getWidth(), window.getHeigth() });
}



//  TEMPORARY TEXT RENDERING
void Engine::RenderText(Shader& s, std::string text, float x, float y, float scale, Color color)
{
	s.use();
	s.setVec3("textColor", color.toVector());
	Matrix4 proj = Matrix4::createSimpleViewProj(window.getWidth(), window.getHeigth());
	s.setMatrix4("projection", proj.getAsFloatPtr());

	int CharMapIDs[512]{ 0 };
	Vector4 CharPosScales[512]{ Vector4::zero };

	Font& arial_font = AssetManager::GetFont("arial_64");
	arial_font.use();
	const int font_size = arial_font.getFontSize();

	AssetManager::GetVertexArray("hud_quad").setActive();

	const float begin_x = x;

	//  iterate through all characters
	std::string::const_iterator c;
	int index = 0;
	for (c = text.begin(); c != text.end(); c++)
	{
		if (index >= 512 - 1)
		{
			break;
		}

		FontCharacter ch = arial_font.getCharacter(*c);

		if (*c == '\n')
		{
			y -= ((ch.Size.y)) * 1.6f * scale;
			x = begin_x;
		}
		else if (*c == ' ')
		{
			x += (ch.Advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
		}
		else
		{
			const float x_pos = x + ch.Bearing.x * scale;
			const float y_pos = y - (float(font_size) - ch.Bearing.y) * scale;
			const float x_scale = float(font_size) * scale;
			const float y_scale = float(font_size) * scale;

			CharPosScales[index] = Vector4{ x_pos, y_pos, x_scale, y_scale };
			CharMapIDs[index] = ch.TextureID;

			x += (ch.Advance >> 6) * scale; // bitshift by 6 (2^6 = 64)

			index++;
			if (index >= 512)
			{
				//  draw array of max 512 chars
				s.setVec4Array("textPosScales", &CharPosScales[0], index);
				s.setIntArray("letterMap", &CharMapIDs[0], index);
				glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, index);

				index = 0;
			}
		}
	}

	//  draw array of remaining chars
	if (index > 0)
	{
		s.setVec4Array("textPosScales", &CharPosScales[0], index);
		s.setIntArray("letterMap", &CharMapIDs[0], index);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, index);
	}

	//  unbind
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}