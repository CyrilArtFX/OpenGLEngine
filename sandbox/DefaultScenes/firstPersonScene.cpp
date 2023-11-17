#include "firstPersonScene.h"

FirstPersonScene::FirstPersonScene() : Scene()
{
}


void FirstPersonScene::load(std::weak_ptr<Renderer> renderer_)
{
	renderer = renderer_.lock();

	//  camera
	camera = std::make_shared<Camera>(Vector3{ 0.0f, 0.0f, -3.0f });
	renderer->setCamera(camera);


	//  shaders, textures and materials
	litObjectShader = std::make_shared<Shader>("object_lit.vert", "object_lit.frag");

	litObjectShader->use(); //  activate the shader on which you want to set the texture unit before doing it
	litObjectShader->setInt("material.diffuse", 0);
	litObjectShader->setInt("material.specular", 1);
	litObjectShader->setInt("material.emissive", 2);

	std::shared_ptr<Texture> container_diffuse = std::make_shared<Texture>("container2.png", GL_RGBA, false); 
	std::shared_ptr<Texture> container_specular = std::make_shared<Texture>("container2_specular.png", GL_RGBA, false);

	crateMat = std::make_shared<LitMaterial>(litObjectShader, container_diffuse, container_specular);


	//  vertex arrays
	float cube_vertices[] =
	{
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
	vaCube = std::make_shared<VertexArray>(cube_vertices, 36);

	float plane_vertices[] =
	{
		// positions           // normals           // texture coords
		-5.0f,  0.0f, -5.0f,   0.0f,  1.0f,  0.0f,   0.0f, 10.0f,
		 5.0f,  0.0f, -5.0f,   0.0f,  1.0f,  0.0f,   10.0f, 10.0f,
		 5.0f,  0.0f,  5.0f,   0.0f,  1.0f,  0.0f,   10.0f, 0.0f,
		 5.0f,  0.0f,  5.0f,   0.0f,  1.0f,  0.0f,   10.0f, 0.0f,
		-5.0f,  0.0f,  5.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
		-5.0f,  0.0f, -5.0f,   0.0f,  1.0f,  0.0f,   0.0f, 10.0f
	};
	vaPlane = std::make_shared<VertexArray>(plane_vertices, 6);


	//  objects
	ground = std::make_shared<Object>(crateMat, vaPlane);
	
	renderer->addObject(ground, crateMat);

	ground->setPosition(Vector3{ 0.0f, -2.0f, 0.0f });


	//  lights
	renderer->addLight(std::make_shared<DirectionalLight>(Directionnal, Color::white, Vector3{ 0.0f, -1.0f, 0.0f }), Directionnal);
}

void FirstPersonScene::unload()
{
	crate1->deleteObject();
	crate2->deleteObject();
	crate3->deleteObject();
	ground->deleteObject();
	vaCube->deleteObjects();
	vaPlane->deleteObjects();
	litObjectShader->deleteProgram();
}


void FirstPersonScene::update(float dt)
{

}


void FirstPersonScene::processInputs(GLFWwindow* glWindow, float dt)
{
	//  move camera
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(Forward, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(Backward, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(Left, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(Right, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(Up, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->ProcessKeyboard(Down, dt);
}

void FirstPersonScene::processMouse(float xOffset, float yOffset)
{
	camera->ProcessMouseMovement(xOffset, yOffset);
}

void FirstPersonScene::processScroll(float scrollOffset)
{
	camera->ProcessMouseScroll(scrollOffset);
}
