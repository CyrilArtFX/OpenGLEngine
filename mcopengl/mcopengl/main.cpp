#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rendering/shader.h"

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

	Shader basicShader("Shaders/basic.vert", "Shaders/basic.frag");


	//  triangles vertices data
	float vertices[] =
	{
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//  setup vertex buffer object and vertex array object
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //  bind the VAO before binding the vertex buffer, and before configuring vertex attributes

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//  position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//  color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//  main loop
	while (!glfwWindowShouldClose(window))
	{
		//  inputs part
		// -------------
		processInput(window);


		//  rendering part
		// ----------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //  clear window with flat color

		//  draw the holy triangle
		basicShader.use();

		//double timeValue = glfwGetTime();

		glBindVertexArray(VAO); //  select VAO to use
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//  events and buffer swap
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	//  delete all resources that are not necessary anymore (optionnal)
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	basicShader.deleteProgram();


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