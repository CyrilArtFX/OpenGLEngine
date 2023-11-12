#include "game.h"

#include <Rendering/shader.h>
#include <Rendering/vertexArray.h>
#include <Objects/object.h>
#include <Utils/Color.h>

#include <Objects/Lights/DirectionalLight.h>
#include <Objects/Lights/PointLight.h>
#include <Objects/Lights/SpotLight.h>

#include <Materials/litMaterial.h>
#include <Materials/flatEmissiveMaterial.h>


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
	renderer = std::make_unique<Renderer>(Color{ 50, 75, 75, 255 });


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
	Shader litObjectShader("Shaders/object_lit.vert", "Shaders/object_lit.frag");
	Shader flatEmissiveShader("Shaders/flat_emissive.vert", "Shaders/flat_emissive.frag");

	//  manually set the textures unit on the shader (need to be done only once)
	litObjectShader.use(); //  activate the shader on which you want to set the texture unit before doing it
	litObjectShader.setInt("material.diffuse", 0);
	litObjectShader.setInt("material.specular", 1);
	litObjectShader.setInt("material.emissive", 2);


	//  create textures
	std::shared_ptr<Texture> container_diffuse = std::make_shared<Texture>("Resources/container2.png", GL_RGBA, false);
	std::shared_ptr<Texture> container_specular = std::make_shared<Texture>("Resources/container2_specular.png", GL_RGBA, false);
	std::shared_ptr<Texture> container_emissive = std::make_shared<Texture>("Resources/matrix.jpg", GL_RGB, false);


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
	std::shared_ptr<VertexArray> vaCube = std::make_shared<VertexArray>(cubeVertices, 36);

	std::shared_ptr<LitMaterial> containerMat = std::make_shared<LitMaterial>(litObjectShader, container_diffuse, container_specular);
	std::shared_ptr<FlatEmissiveMaterial> lightSourceMat = std::make_shared<FlatEmissiveMaterial>(flatEmissiveShader, Vector3(1.0f, 1.0f, 1.0f));


	std::shared_ptr<Object> cube_1 = std::make_shared<Object>(containerMat, vaCube);
	std::shared_ptr<Object> cube_2 = std::make_shared<Object>(containerMat, vaCube); 
	std::shared_ptr<Object> cube_3 = std::make_shared<Object>(containerMat, vaCube); 

	std::shared_ptr<Object> lightCube_1 = std::make_shared<Object>(lightSourceMat, vaCube);
	std::shared_ptr<Object> lightCube_2 = std::make_shared<Object>(lightSourceMat, vaCube);


	renderer->addObject(cube_1, containerMat);
	renderer->addObject(cube_2, containerMat);
	renderer->addObject(cube_3, containerMat);
	renderer->addObject(lightCube_1, lightSourceMat);
	renderer->addObject(lightCube_2, lightSourceMat);


	lightCube_1->setPosition(Vector3{1.0f, 2.0f, 1.0f});  
	lightCube_1->setScale(0.2f);  
	lightCube_2->setPosition(Vector3{ 1.5f, 1.0f, -0.5f }); 
	lightCube_2->setScale(0.2f); 

	cube_1->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	cube_2->setPosition(Vector3{ 2.0f, 1.5f, 2.0f }); 
	cube_3->setPosition(Vector3{ 2.0f, -1.0f, -1.0f }); 


	std::shared_ptr<SpotLight> flashLight = std::make_shared<SpotLight>(Spot, Color::white, Vector3::zero, Vector3::unitX); 

	renderer->addLight(std::make_shared<DirectionalLight>(Directionnal, Color::white, Vector3{ -0.4f, -0.5f, 1.0f }), Directionnal);
	renderer->addLight(std::make_shared<PointLight>(Point, Color::white, Vector3{ 1.0f, 2.0f, 1.0f }), Point);
	renderer->addLight(std::make_shared<PointLight>(Point, Color::white, Vector3{ 1.5f, 1.0f, -0.5f }), Point);
	renderer->addLight(flashLight, Spot);



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

		//  those two matrix should be put in the renderer logic later
		Matrix4 view = camera->GetViewMatrix(); 
		Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(camera->getFov()), window->getWidth(), window->getHeigth(), 0.1f, 100.0f); 

		flashLight->setPosition(camera->getPosition());
		flashLight->setDirection(camera->getFront());

		renderer->draw(view, projection, camera->getPosition());



		//  events and buffer swap
		glfwSwapBuffers(window->getGLFWwindow());
		glfwPollEvents();
	}


	//  delete all resources that are not necessary anymore (optionnal)
	cube_1->deleteObject();
	cube_2->deleteObject(); 
	cube_3->deleteObject();  
	lightCube_1->deleteObject();  
	lightCube_2->deleteObject(); 
	litObjectShader.deleteProgram();
	flatEmissiveShader.deleteProgram();
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
