#include "game.h"


//  declare callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



bool Game::initialize(int wndw_width, int wndw_height, std::string wndw_name, bool wndw_capturemouse)
{
	//  create window and initialize glfw
	window = Window(wndw_width, wndw_height, wndw_name.c_str(), wndw_capturemouse);

	GLFWwindow* glWindow = window.getGLFWwindow();
	if (glWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwSetFramebufferSizeCallback(glWindow, framebuffer_size_callback); //  link window resize callback function
	glfwSetCursorPosCallback(glWindow, mouse_callback); //  link mouse pos callback function
	glfwSetScrollCallback(glWindow, scroll_callback); //  link mouse scroll callback function


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


	//  END INITIALIZATION PART
	//  =======================



	//  ---------------------------------------------------------------------------------------------------
	//  Everything below this part in this function should be later implemented with a Scene loading system


	camera = Camera(Vector3{ 0.0f, 0.0f, -3.0f });

	//  build and compile shaders
	//Shader basicShader("Shaders/basic.vert", "Shaders/basic.frag");
	//Shader textureShader("Shaders/texture.vert", "Shaders/texture.frag");
	//Shader object3DShader("Shaders/object.vert", "Shaders/object.frag");
	lightObj3DShader = Shader("Shaders/object.vert", "Shaders/lightedobject.frag");
	lightShader = Shader("Shaders/light.vert", "Shaders/light.frag");

	//  cube vertices data
	float cubeVertices[180] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	cube = VertexArray(cubeVertices, 36);

	lightCube = VertexArray(cubeVertices, 36);


	containerTex = Texture("Resources/container.jpg", GL_RGB, true);
	faceTex = Texture("Resources/awesomeface.png", GL_RGBA, true);

	//  manually set the textures unit on the shader (need to be done only once)
	lightObj3DShader.use(); //  activate the shader on which you want to set the texture unit before doing it
	lightObj3DShader.setInt("texture1", 0);
	lightObj3DShader.setInt("texture2", 1);


	return true;
}


void Game::loop()
{
	//  main loop
	while (!glfwWindowShouldClose(window.getGLFWwindow()))
	{
		//  time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;



		//  inputs part
		// -------------
		processInput(window.getGLFWwindow());


		//  rendering part
		// ----------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //  clear window with flat color



		//float timeValue = glfwGetTime();



		//  draw
		Matrix4 view = camera.GetViewMatrix();
		Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(camera.getFov()), window.getWidth(), window.getHeigth(), 0.1f, 100.0f);
		Matrix4 model = Matrix4::identity;

		lightShader.use();
		lightShader.setVec3("lightColor", lightColor);

		model = Matrix4::createScale(Vector3{ 0.2f, 0.2f, 0.2f }) * Matrix4::createTranslation(lightPos);

		lightShader.setMatrix4("view", view.getAsFloatPtr());
		lightShader.setMatrix4("projection", projection.getAsFloatPtr());
		lightShader.setMatrix4("model", model.getAsFloatPtr());

		lightCube.setActive();
		glDrawArrays(GL_TRIANGLES, 0, lightCube.getNBVertices());



		lightObj3DShader.use();

		glActiveTexture(GL_TEXTURE0);
		containerTex.use();
		glActiveTexture(GL_TEXTURE1);
		faceTex.use();

		lightObj3DShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightObj3DShader.setVec3("lightColor", lightColor);

		model = Matrix4::identity;

		lightObj3DShader.setMatrix4("view", view.getAsFloatPtr());
		lightObj3DShader.setMatrix4("projection", projection.getAsFloatPtr());
		lightObj3DShader.setMatrix4("model", model.getAsFloatPtr());

		cube.setActive();
		glDrawArrays(GL_TRIANGLES, 0, cube.getNBVertices());



		//  events and buffer swap
		glfwSwapBuffers(window.getGLFWwindow());
		glfwPollEvents();
	}
}


void Game::close()
{
	//  This should also be put in a scene logic
	//  ----------------------------------------
	
	//  delete all resources that are not necessary anymore (optionnal)
	cube.deleteObjects();
	lightCube.deleteObjects();
	lightObj3DShader.deleteProgram();
	lightShader.deleteProgram();




	//  properly clear GLFW before closing app (will stay here)
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
		camera.ProcessKeyboard(Forward, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Backward, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Left, deltaTime);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Right, deltaTime);
}


//  class member redirected callback functions
void Game::windowResize(GLFWwindow* glWindow, int width, int height)
{
	glViewport(0, 0, width, height); //  resize OpenGL viewport when GLFW is resized
	window.changeSize(width, height);
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void Game::processScroll(GLFWwindow* glWindow, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(float(yoffset));
}



//  redirect callback functions
void framebuffer_size_callback(GLFWwindow* glWindow, int width, int height)
{
	Game::instance().windowResize(glWindow, width, height);
}

void mouse_callback(GLFWwindow* glWindow, double xpos, double ypos)
{
	Game::instance().processMouse(glWindow, xpos, ypos);
}

void scroll_callback(GLFWwindow* glWindow, double xoffset, double yoffset)
{
	Game::instance().processScroll(glWindow, xoffset, yoffset);
}
