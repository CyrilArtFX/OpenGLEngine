#include "ExpositionScene.h"

#include <GLFW/glfw3.h>


ExpositionScene::ExpositionScene() : Scene()
{
}


void ExpositionScene::load(std::weak_ptr<Renderer> renderer_)
{
	renderer = renderer_.lock();

	//  camera
	currentCam = std::make_shared<Camera>(Vector3{ 0.0f, 0.0f, -3.0f });
	renderer->setCamera(currentCam);


	//  shaders, textures and materials
	litObjectShader = std::make_shared<Shader>("Lit/object_lit.vert", "Lit/object_lit.frag", Lit);
	flatEmissiveShader = std::make_shared<Shader>("Unlit/flat_emissive.vert", "Unlit/flat_emissive.frag", Unlit);

	litObjectShader->use(); //  activate the shader on which you want to set the texture unit before doing it
	litObjectShader->setInt("material.diffuse", 0);
	litObjectShader->setInt("material.specular", 1);
	litObjectShader->setInt("material.emissive", 2);

	std::shared_ptr<Texture> container_diffuse = std::make_shared<Texture>("container2.png", GL_RGBA, false);
	std::shared_ptr<Texture> container_specular = std::make_shared<Texture>("container2_specular.png", GL_RGBA, false);
	std::shared_ptr<Texture> container_emissive = std::make_shared<Texture>("matrix.jpg", GL_RGB, false);

	containerMat = std::make_shared<LitMaterial>(litObjectShader, container_diffuse, container_specular);
	lightSourceMat = std::make_shared<FlatEmissiveMaterial>(flatEmissiveShader, Vector3(1.0f, 1.0f, 1.0f));


	//  vertex arrays and objects
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

	cube1 = std::make_shared<Object>(containerMat, vaCube);
	cube2 = std::make_shared<Object>(containerMat, vaCube);
	cube3 = std::make_shared<Object>(containerMat, vaCube);
	lightCube1 = std::make_shared<Object>(lightSourceMat, vaCube);
	lightCube2 = std::make_shared<Object>(lightSourceMat, vaCube);

	renderer->addObject(cube1, litObjectShader);
	renderer->addObject(cube2, litObjectShader);
	renderer->addObject(cube3, litObjectShader);
	renderer->addObject(lightCube1, flatEmissiveShader);
	renderer->addObject(lightCube2, flatEmissiveShader);

	cube1->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	cube1->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(45.0f) });
	cube2->setPosition(Vector3{ 2.0f, 1.5f, 2.0f });
	cube3->setPosition(Vector3{ 2.0f, -1.0f, -1.0f });
	lightCube1->setPosition(Vector3{ 1.0f, 2.0f, 1.0f });
	lightCube1->setScale(0.2f);
	lightCube2->setPosition(Vector3{ 1.5f, 1.0f, -0.5f });
	lightCube2->setScale(0.2f);


	//  lights
	flashLight = std::make_shared<SpotLight>(Spot, Color::white, Vector3::zero, Vector3::unitX);

	renderer->addLight(std::make_shared<DirectionalLight>(Directionnal, Color::white, Vector3{ -0.4f, -0.5f, 1.0f }), Directionnal);
	renderer->addLight(std::make_shared<PointLight>(Point, Color::white, Vector3{ 1.0f, 2.0f, 1.0f }), Point);
	renderer->addLight(std::make_shared<PointLight>(Point, Color::white, Vector3{ 1.5f, 1.0f, -0.5f }), Point);
	renderer->addLight(flashLight, Spot);
}


void ExpositionScene::unload()
{
	cube1->deleteObject();
	cube2->deleteObject();
	cube3->deleteObject();
	lightCube1->deleteObject();
	lightCube2->deleteObject();
	vaCube->deleteObjects();
	litObjectShader->deleteProgram();
	flatEmissiveShader->deleteProgram();
}


void ExpositionScene::update(float dt)
{
	flashLight->setPosition(currentCam->getPosition());
	flashLight->setDirection(currentCam->getForward());

	cube3->incrementRotation(Quaternion{ Vector3::unitX, Maths::toRadians(90.0f) * dt });
}

void ExpositionScene::processInputs(GLFWwindow* glWindow, float dt)
{
	//  move camera
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
		currentCam->freecamKeyboard(Forward, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		currentCam->freecamKeyboard(Backward, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		currentCam->freecamKeyboard(Left, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		currentCam->freecamKeyboard(Right, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		currentCam->freecamKeyboard(Up, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		currentCam->freecamKeyboard(Down, dt);

}

void ExpositionScene::processMouse(float xOffset, float yOffset)
{
	currentCam->freecamMouseMovement(xOffset, yOffset);
}

void ExpositionScene::processScroll(float scrollOffset)
{
	currentCam->freecamMouseScroll(scrollOffset);
}
