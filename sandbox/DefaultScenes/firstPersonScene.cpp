#include "firstPersonScene.h"

FirstPersonScene::FirstPersonScene() : Scene()
{
}


void FirstPersonScene::load(std::weak_ptr<Renderer> renderer_)
{
	renderer = renderer_.lock();

	//  shaders, textures and materials
	litObjectShader = std::make_shared<Shader>("object_lit.vert", "object_lit.frag");

	litObjectShader->use(); //  activate the shader on which you want to set the texture unit before doing it
	litObjectShader->setInt("material.diffuse", 0);
	litObjectShader->setInt("material.specular", 1);
	litObjectShader->setInt("material.emissive", 2);

	std::shared_ptr<Texture> crate_diffuse = std::make_shared<Texture>("container2.png", GL_RGBA, false); 
	std::shared_ptr<Texture> crate_specular = std::make_shared<Texture>("container2_specular.png", GL_RGBA, false);
	std::shared_ptr<Texture> ground_diffuse = std::make_shared<Texture>("pavement.jpg", GL_RGB, false);
	std::shared_ptr<Texture> ground_specular = std::make_shared<Texture>("Default/black.png", GL_RGBA, false);

	crateMat = std::make_shared<LitMaterial>(litObjectShader, crate_diffuse, crate_specular);
	groundMat = std::make_shared<LitMaterial>(litObjectShader, ground_diffuse, ground_specular);


	//  player (camera)
	player = std::make_unique<Player>(1.5f, groundMat); 
	renderer->setCamera(player->getCamera());


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
		-5.0f,  0.0f, -5.0f,   0.0f,  1.0f,  0.0f,    0.0f, 10.0f,
		 5.0f,  0.0f, -5.0f,   0.0f,  1.0f,  0.0f,   10.0f, 10.0f,
		 5.0f,  0.0f,  5.0f,   0.0f,  1.0f,  0.0f,   10.0f,  0.0f,
		 5.0f,  0.0f,  5.0f,   0.0f,  1.0f,  0.0f,   10.0f,  0.0f,
		-5.0f,  0.0f,  5.0f,   0.0f,  1.0f,  0.0f,    0.0f,  0.0f,
		-5.0f,  0.0f, -5.0f,   0.0f,  1.0f,  0.0f,    0.0f, 10.0f
	};
	vaPlane = std::make_shared<VertexArray>(plane_vertices, 6);


	//  objects
	ground = std::make_shared<Object>(groundMat, vaPlane);
	crate1 = std::make_shared<Object>(crateMat, vaCube);
	crate2 = std::make_shared<Object>(crateMat, vaCube);
	crate3 = std::make_shared<Object>(crateMat, vaCube);
	
	renderer->addObject(ground, groundMat);
	renderer->addObject(crate1, crateMat);
	renderer->addObject(crate2, crateMat);
	renderer->addObject(crate3, crateMat);

	ground->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	crate1->setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2->setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3->setPosition(Vector3{ -3.5f, 0.5f, -1.0f });


	//  lights
	Vector3 dir_light{ 0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	renderer->addLight(std::make_shared<DirectionalLight>(Directionnal, Color::white, dir_light), Directionnal);
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
	player->update(dt);
}


void FirstPersonScene::processInputs(GLFWwindow* glWindow, float dt)
{
	player->processInputs(glWindow, dt);
}

void FirstPersonScene::processMouse(float xOffset, float yOffset)
{
	player->processMouse(xOffset, yOffset);
}

void FirstPersonScene::processScroll(float scrollOffset)
{
	player->processScroll(scrollOffset);
}
