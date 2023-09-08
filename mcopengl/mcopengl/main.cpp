#include <glad/glad.h>
#include <GLFW/glfw3.h>

//  if this line is not here, the project don't compile (bruh)
#define STB_IMAGE_IMPLEMENTATION

#include "Rendering/shader.h"
#include "Rendering/texture.h"
#include "Rendering/vertexArray.h"

#include "Maths/Matrix4.h"

#include <iostream>


//  declare functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


//  global settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 720;


int main()
{
	//  initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//  create GLFW window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Minecraft OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //  link our window resize callback function


	//  initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//  configure global OpenGL properties
	glEnable(GL_DEPTH_TEST);


	//  build and compile shaders
	Shader basicShader("Shaders/basic.vert", "Shaders/basic.frag");
	Shader textureShader("Shaders/texture.vert", "Shaders/texture.frag");
	Shader object3DShader("Shaders/object.vert", "Shaders/object.frag");


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

	VertexArray cube = VertexArray(cubeVertices, 36);


	Texture containerTex("Resources/container.jpg", GL_RGB, true);
	Texture faceTex("Resources/awesomeface.png", GL_RGBA, true);


	//  manually set the textures unit on the shader (need to be done only once)
	object3DShader.use(); //  activate the shader on which you want to set the texture unit before doing it
	object3DShader.setInt("texture1", 0);
	object3DShader.setInt("texture2", 1);

	Vector3 cubePositions[] = {
		Vector3{0.0f, 0.0f, 0.0f},
		Vector3{2.0f, 5.0f, 15.0f},
		Vector3{-1.5f, -2.2f, 2.5f},
		Vector3{-3.8f, -2.0f, 12.3f},
		Vector3{2.4f, -0.4f, 3.5f},
		Vector3{-1.7f, 3.0f, 7.5f},
		Vector3{1.3f, -2.0f, 2.5f},
		Vector3{1.5f, 2.0f, 2.5f},
		Vector3{1.5f, 0.2f, 1.5f},
		Vector3{-1.3f, 1.0f, 1.5f}
	};


	Matrix4 view = Matrix4::createTranslation(Vector3{ 0.0f, 0.0f, 3.0f });
	Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(45.0f), 1024, 720, 0.1f, 100.0f);


	//  main loop
	while (!glfwWindowShouldClose(window))
	{
		//  inputs part
		// -------------
		processInput(window);


		//  rendering part
		// ----------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //  clear window with flat color

		//  draw
		object3DShader.use();

		glActiveTexture(GL_TEXTURE0);
		containerTex.use();
		glActiveTexture(GL_TEXTURE1);
		faceTex.use();


		//float timeValue = glfwGetTime();

		Vector3 rotationAxis = Vector3{ 1.0f, 0.3f, 0.5f };
		rotationAxis.normalize();

		object3DShader.setMatrix4("view", view.getAsFloatPtr());
		object3DShader.setMatrix4("projection", projection.getAsFloatPtr());

		cube.setActive();
		glDrawArrays(GL_TRIANGLES, 0, cube.getNBVertices());

		for (int i = 0; i < 10; i++)
		{
			Quaternion rotation = Quaternion{ rotationAxis, Maths::toRadians(i * 20.0f) };
			Matrix4 model = Matrix4::createFromQuaternion(rotation) * 
				Matrix4::createTranslation(cubePositions[i]);
				
			object3DShader.setMatrix4("model", model.getAsFloatPtr());

			glDrawArrays(GL_TRIANGLES, 0, cube.getNBVertices());
		}



		//  events and buffer swap
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	//  delete all resources that are not necessary anymore (optionnal)
	cube.deleteObjects();
	basicShader.deleteProgram();
	textureShader.deleteProgram();
	object3DShader.deleteProgram();


	//  properly clear GLFW before closing app
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); //  resize OpenGL viewport when GLFW is resized
}

void processInput(GLFWwindow* window)
{
	//  close window when escape is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}