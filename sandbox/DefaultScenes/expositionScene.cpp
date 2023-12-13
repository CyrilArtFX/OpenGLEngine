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
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", ShaderType::Lit);
	AssetManager::CreateShaderProgram("flat_emissive", "Unlit/flat_emissive.vert", "Unlit/flat_emissive.frag", ShaderType::Unlit);

	AssetManager::LoadTexture("container_diffuse", "container2.png", TextureType::Diffuse, GL_RGBA, false);
	AssetManager::LoadTexture("container_specular", "container2_specular.png", TextureType::Specular, GL_RGBA, false);
	AssetManager::LoadTexture("container_emissive", "matrix.jpg", TextureType::Emissive, GL_RGB, false);
	AssetManager::LoadTexture("black_emissive", "Default/black.png", TextureType::Emissive, GL_RGBA, false);

	Material& container_mat = AssetManager::CreateMaterial("container", &AssetManager::GetShader("lit_object"));
	container_mat.addTexture(&AssetManager::GetTexture("container_diffuse"));
	container_mat.addTexture(&AssetManager::GetTexture("container_specular"));
	container_mat.addTexture(&AssetManager::GetTexture("black_emissive"));
	container_mat.addParameter("material.shininess", 32.0f);

	Material& light_source_mat = AssetManager::CreateMaterial("light_source", &AssetManager::GetShader("flat_emissive"));
	light_source_mat.addParameter("emissive", 1.0f, 1.0f, 1.0f);

	renderer->addMaterial(&AssetManager::GetMaterial("container"));
	renderer->addMaterial(&AssetManager::GetMaterial("light_source"));


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

	AssetManager::CreateModel("container");
	AssetManager::GetModel("container").addMesh(&AssetManager::GetSingleMesh("cube"), &AssetManager::GetMaterial("container"));

	AssetManager::CreateModel("light_cube");
	AssetManager::GetModel("light_cube").addMesh(&AssetManager::GetSingleMesh("cube"), &AssetManager::GetMaterial("light_source"));

	cube1.addModel(&AssetManager::GetModel("container"));
	cube2.addModel(&AssetManager::GetModel("container"));
	cube3.addModel(&AssetManager::GetModel("container"));

	lightCube1.addModel(&AssetManager::GetModel("light_cube"));
	lightCube2.addModel(&AssetManager::GetModel("light_cube"));

	renderer->addObject(&cube1);
	renderer->addObject(&cube2);
	renderer->addObject(&cube3);
	renderer->addObject(&lightCube1);
	renderer->addObject(&lightCube2);

	cube1.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	cube1.setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(45.0f) });
	cube2.setPosition(Vector3{ 2.0f, 1.5f, 2.0f });
	cube3.setPosition(Vector3{ 2.0f, -1.0f, -1.0f });
	lightCube1.setPosition(Vector3{ 1.0f, 2.0f, 1.0f });
	lightCube1.setScale(0.2f);
	lightCube2.setPosition(Vector3{ 1.5f, 1.0f, -0.5f });
	lightCube2.setScale(0.2f);


	//  lights
	sunLight.load(Color::white, Vector3{ -0.4f, -0.5f, 1.0f });
	pointLight1.load(Color::white, Vector3{ 1.0f, 2.0f, 1.0f });
	pointLight2.load(Color::white, Vector3{ 1.5f, 1.0f, -0.5f });
	flashLight.load(Color::white, Vector3::zero, Vector3::unitX);

	renderer->addLight(&sunLight);
	renderer->addLight(&pointLight1);
	renderer->addLight(&pointLight2);
	renderer->addLight(&flashLight);
}


void ExpositionScene::unload()
{
}


void ExpositionScene::update(float dt)
{
	flashLight.setPosition(currentCam->getPosition());
	flashLight.setDirection(currentCam->getForward());

	cube3.incrementRotation(Quaternion{ Vector3::unitX, Maths::toRadians(90.0f) * dt });
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
