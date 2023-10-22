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
	//  run initialization

	camera = std::make_unique<Camera>(Vector3{ 0.0f, 0.0f, -3.0f });


	//  build and compile shaders
	//Shader basicShader("Shaders/basic.vert", "Shaders/basic.frag");
	//Shader textureShader("Shaders/texture.vert", "Shaders/texture.frag");
	//Shader object3DShader("Shaders/object.vert", "Shaders/object.frag");
	Shader lightObj3DShader("Shaders/object.vert", "Shaders/lightedobject.frag");
	Shader lightShader("Shaders/light.vert", "Shaders/light.frag");

	//  cube vertices data
	float cubeVertices[] = {
		// positions           // normals           // texture coords
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
		
		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f
	};

	VertexArray cube(cubeVertices, 36);

	
	/*  the texture logic should be reimplemented later
	Texture containerTex("Resources/container.jpg", GL_RGB, true);
	Texture faceTex("Resources/awesomeface.png", GL_RGBA, true);

	//  manually set the textures unit on the shader (need to be done only once)
	lightObj3DShader.use(); //  activate the shader on which you want to set the texture unit before doing it
	lightObj3DShader.setInt("texture1", 0);
	lightObj3DShader.setInt("texture2", 1);
	*/


	Vector3 lightColor{ 1.0f, 1.0f, 1.0f };
	lightPos = Vector3{ 1.2f, 1.0f, 2.0f };



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


		//  rendering part
		// ----------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //  clear window with flat color



		//float timeValue = glfwGetTime();



		//  draw
		Matrix4 view = camera->GetViewMatrix();
		Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(camera->getFov()), window->getWidth(), window->getHeigth(), 0.1f, 100.0f);
		Matrix4 model = Matrix4::identity;

		lightShader.use();
		lightShader.setVec3("lightColor", lightColor);

		model = Matrix4::createScale(Vector3{ 0.2f, 0.2f, 0.2f }) * Matrix4::createTranslation(lightPos);

		lightShader.setMatrix4("view", view.getAsFloatPtr());
		lightShader.setMatrix4("projection", projection.getAsFloatPtr());
		lightShader.setMatrix4("model", model.getAsFloatPtr());

		cube.setActive();
		glDrawArrays(GL_TRIANGLES, 0, cube.getNBVertices());



		lightObj3DShader.use();

		/*glActiveTexture(GL_TEXTURE0);
		containerTex.use();
		glActiveTexture(GL_TEXTURE1);
		faceTex.use();*/

		lightObj3DShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightObj3DShader.setVec3("lightColor", lightColor);
		lightObj3DShader.setVec3("lightPos", lightPos);
		lightObj3DShader.setVec3("viewPos", camera->getPosition());

		model = Matrix4::identity;
		Matrix4 normalMatrix = model * view;
		normalMatrix.invert();
		normalMatrix.transpose();

		lightObj3DShader.setMatrix4("view", view.getAsFloatPtr());
		lightObj3DShader.setMatrix4("projection", projection.getAsFloatPtr());
		lightObj3DShader.setMatrix4("model", model.getAsFloatPtr());
		lightObj3DShader.setMatrix4("normalMatrix", normalMatrix.getAsFloatPtr());

		cube.setActive();
		glDrawArrays(GL_TRIANGLES, 0, cube.getNBVertices());



		//  events and buffer swap
		glfwSwapBuffers(window->getGLFWwindow());
		glfwPollEvents();
	}


	//  delete all resources that are not necessary anymore (optionnal)
	cube.deleteObjects();
	lightObj3DShader.deleteProgram();
	lightShader.deleteProgram();
}


void Game::close()
{
	//  properly clear GLFW before closing app
	glfwTerminate();
}





void Game::processInput(GLFWwindow* glWindow)
{
	//  close window when escape is pressed
	if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glWindow, true);
	}

	//  move camera
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(Forward, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(Backward, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(Left, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(Right, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(Up, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->ProcessKeyboard(Down, deltaTime);


	//  move light (temp)
	float light_speed = 2.0f;

	if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_PRESS)
		lightPos += Vector3{ 0.0f, 0.0f, 1.0f } * deltaTime * light_speed;

	if (glfwGetKey(glWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		lightPos += Vector3{ 0.0f, 0.0f, -1.0f } * deltaTime * light_speed;

	if (glfwGetKey(glWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		lightPos += Vector3{ -1.0f, 0.0f, 0.0f } * deltaTime * light_speed;

	if (glfwGetKey(glWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
		lightPos += Vector3{ 1.0f, 0.0f, 0.0f } * deltaTime * light_speed;

	if (glfwGetKey(glWindow, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		lightPos += Vector3{ 0.0f, 1.0f, 0.0f } * deltaTime * light_speed;

	if (glfwGetKey(glWindow, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		lightPos += Vector3{ 0.0f, -1.0f, 0.0f } * deltaTime * light_speed;
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

	camera->ProcessMouseMovement(xoffset, yoffset);
}

void Game::processScroll(GLFWwindow* glWindow, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(float(yoffset));
}
