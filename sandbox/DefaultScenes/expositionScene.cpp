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

	std::shared_ptr<Texture> container_diffuse = std::make_shared<Texture>("container2.png", TextureType::Diffuse, GL_RGBA, false);
	std::shared_ptr<Texture> container_specular = std::make_shared<Texture>("container2_specular.png", TextureType::Specular, GL_RGBA, false);
	//std::shared_ptr<Texture> container_emissive = std::make_shared<Texture>("matrix.jpg", TextureType::Emissive, GL_RGB, false);
	std::shared_ptr<Texture> container_emissive = std::make_shared<Texture>("Default/black.png", TextureType::Emissive, GL_RGBA, false);

	containerMat = std::make_shared<Material>(litObjectShader);
	containerMat->addTexture(container_diffuse);
	containerMat->addTexture(container_specular);
	containerMat->addTexture(container_emissive);
	containerMat->addParameter("material.shininess", 32.0f);

	lightSourceMat = std::make_shared<Material>(flatEmissiveShader);
	lightSourceMat->addParameter("emissive", 1.0f, 1.0f, 1.0f);

	renderer->addMaterial(containerMat);
	renderer->addMaterial(lightSourceMat);


	//  meshes, models and objects
	std::vector<Vertex> cube_vertices
	{
		// positions                           // normals                      // tex coords
		Vertex{Vector3{-0.5f, -0.5f, -0.5f},   Vector3{ 0.0f,  0.0f, -1.0f},   Vector2{0.0f, 0.0f}},
		Vertex{Vector3{ 0.5f, -0.5f, -0.5f},   Vector3{ 0.0f,  0.0f, -1.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{ 0.5f,  0.5f, -0.5f},   Vector3{ 0.0f,  0.0f, -1.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{ 0.5f,  0.5f, -0.5f},   Vector3{ 0.0f,  0.0f, -1.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{-0.5f,  0.5f, -0.5f},   Vector3{ 0.0f,  0.0f, -1.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{-0.5f, -0.5f, -0.5f},   Vector3{ 0.0f,  0.0f, -1.0f},   Vector2{0.0f, 0.0f}},

		Vertex{Vector3{-0.5f, -0.5f,  0.5f},   Vector3{ 0.0f,  0.0f,  1.0f},   Vector2{0.0f, 0.0f}},
		Vertex{Vector3{ 0.5f, -0.5f,  0.5f},   Vector3{ 0.0f,  0.0f,  1.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{ 0.5f,  0.5f,  0.5f},   Vector3{ 0.0f,  0.0f,  1.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{ 0.5f,  0.5f,  0.5f},   Vector3{ 0.0f,  0.0f,  1.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{-0.5f,  0.5f,  0.5f},   Vector3{ 0.0f,  0.0f,  1.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{-0.5f, -0.5f,  0.5f},   Vector3{ 0.0f,  0.0f,  1.0f},   Vector2{0.0f, 0.0f}},

		Vertex{Vector3{-0.5f,  0.5f,  0.5f},   Vector3{-1.0f,  0.0f,  0.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{-0.5f,  0.5f, -0.5f},   Vector3{-1.0f,  0.0f,  0.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{-0.5f, -0.5f, -0.5f},   Vector3{-1.0f,  0.0f,  0.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{-0.5f, -0.5f, -0.5f},   Vector3{-1.0f,  0.0f,  0.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{-0.5f, -0.5f,  0.5f},   Vector3{-1.0f,  0.0f,  0.0f},   Vector2{0.0f, 0.0f}},
		Vertex{Vector3{-0.5f,  0.5f,  0.5f},   Vector3{-1.0f,  0.0f,  0.0f},   Vector2{1.0f, 0.0f}},

		Vertex{Vector3{ 0.5f,  0.5f,  0.5f},   Vector3{ 1.0f,  0.0f,  0.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{ 0.5f,  0.5f, -0.5f},   Vector3{ 1.0f,  0.0f,  0.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{ 0.5f, -0.5f, -0.5f},   Vector3{ 1.0f,  0.0f,  0.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{ 0.5f, -0.5f, -0.5f},   Vector3{ 1.0f,  0.0f,  0.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{ 0.5f, -0.5f,  0.5f},   Vector3{ 1.0f,  0.0f,  0.0f},   Vector2{0.0f, 0.0f}},
		Vertex{Vector3{ 0.5f,  0.5f,  0.5f},   Vector3{ 1.0f,  0.0f,  0.0f},   Vector2{1.0f, 0.0f}},

		Vertex{Vector3{-0.5f, -0.5f, -0.5f},   Vector3{ 0.0f, -1.0f,  0.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{ 0.5f, -0.5f, -0.5f},   Vector3{ 0.0f, -1.0f,  0.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{ 0.5f, -0.5f,  0.5f},   Vector3{ 0.0f, -1.0f,  0.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{ 0.5f, -0.5f,  0.5f},   Vector3{ 0.0f, -1.0f,  0.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{-0.5f, -0.5f,  0.5f},   Vector3{ 0.0f, -1.0f,  0.0f},   Vector2{0.0f, 0.0f}},
		Vertex{Vector3{-0.5f, -0.5f, -0.5f},   Vector3{ 0.0f, -1.0f,  0.0f},   Vector2{0.0f, 1.0f}},

		Vertex{Vector3{-0.5f,  0.5f, -0.5f},   Vector3{ 0.0f,  1.0f,  0.0f},   Vector2{0.0f, 1.0f}},
		Vertex{Vector3{ 0.5f,  0.5f, -0.5f},   Vector3{ 0.0f,  1.0f,  0.0f},   Vector2{1.0f, 1.0f}},
		Vertex{Vector3{ 0.5f,  0.5f,  0.5f},   Vector3{ 0.0f,  1.0f,  0.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{ 0.5f,  0.5f,  0.5f},   Vector3{ 0.0f,  1.0f,  0.0f},   Vector2{1.0f, 0.0f}},
		Vertex{Vector3{-0.5f,  0.5f,  0.5f},   Vector3{ 0.0f,  1.0f,  0.0f},   Vector2{0.0f, 0.0f}},
		Vertex{Vector3{-0.5f,  0.5f, -0.5f},   Vector3{ 0.0f,  1.0f,  0.0f},   Vector2{0.0f, 1.0f}}
	};
	AssetManager::LoadSingleMesh("cube", cube_vertices);

	modelContainer = std::make_shared<Model>();
	modelContainer->addMesh(AssetManager::GetSingleMesh("cube"), containerMat);

	modelLightCube = std::make_shared<Model>();
	modelLightCube->addMesh(AssetManager::GetSingleMesh("cube"), lightSourceMat);

	cube1 = std::make_shared<Object>();
	cube1->addModel(modelContainer);
	cube2 = std::make_shared<Object>();
	cube2->addModel(modelContainer);
	cube3 = std::make_shared<Object>();
	cube3->addModel(modelContainer);

	lightCube1 = std::make_shared<Object>();
	lightCube1->addModel(modelLightCube);
	lightCube2 = std::make_shared<Object>();
	lightCube2->addModel(modelLightCube);

	renderer->addObject(cube1);
	renderer->addObject(cube2);
	renderer->addObject(cube3);
	renderer->addObject(lightCube1);
	renderer->addObject(lightCube2);

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
