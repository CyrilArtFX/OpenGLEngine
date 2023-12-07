#include "firstPersonScene.h"

FirstPersonScene::FirstPersonScene() : Scene()
{
}


void FirstPersonScene::load(std::weak_ptr<Renderer> renderer_)
{
	renderer = renderer_.lock();

	//  shaders, textures and materials
	litObjectShader = std::make_shared<Shader>("Lit/object_lit.vert", "Lit/object_lit.frag", Lit);
	bulletShader = std::make_shared<Shader>("Unlit/flat_emissive.vert", "Unlit/flat_emissive.frag", Unlit);

	std::shared_ptr<Texture> crate_diffuse = std::make_shared<Texture>("container2.png", TextureType::Diffuse, GL_RGBA, false); 
	std::shared_ptr<Texture> crate_specular = std::make_shared<Texture>("container2_specular.png", TextureType::Specular, GL_RGBA, false);
	std::shared_ptr<Texture> ground_diffuse = std::make_shared<Texture>("pavement.jpg", TextureType::Diffuse, GL_RGB, false);
	std::shared_ptr<Texture> ground_specular = std::make_shared<Texture>("Default/black.png", TextureType::Specular, GL_RGBA, false);
	std::shared_ptr<Texture> black_emissive = std::make_shared<Texture>("Default/black.png", TextureType::Emissive, GL_RGBA, false);

	crateMat = std::make_shared<Material>(litObjectShader);
	crateMat->addTexture(crate_diffuse);
	crateMat->addTexture(crate_specular);
	crateMat->addTexture(black_emissive);
	crateMat->addParameter("material.shininess", 32.0f);

	groundMat = std::make_shared<Material>(litObjectShader);
	groundMat->addTexture(ground_diffuse);
	groundMat->addTexture(ground_specular);
	groundMat->addTexture(black_emissive);
	groundMat->addParameter("material.shininess", 32.0f);

	std::shared_ptr<Material> bullet_mat = std::make_shared<Material>(bulletShader);
	bullet_mat->addParameter("emissive", 1.0f, 1.0f, 1.0f);

	renderer->addMaterial(crateMat);
	renderer->addMaterial(groundMat);
	renderer->addMaterial(bullet_mat);


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
	meshCube = std::make_shared<Mesh>(cube_vertices);

	std::vector<Vertex> plane_vertices
	{
		// positions                         // normals                   // tex coords
		Vertex{Vector3{-5.0f, 0.0f, -5.0f},  Vector3{ 0.0f, 1.0f, 0.0f},  Vector2{ 0.0f,  0.0f}},
		Vertex{Vector3{ 5.0f, 0.0f, -5.0f},  Vector3{ 0.0f, 1.0f, 0.0f},  Vector2{10.0f,  0.0f}},
		Vertex{Vector3{ 5.0f, 0.0f,  5.0f},  Vector3{ 0.0f, 1.0f, 0.0f},  Vector2{10.0f, 10.0f}},
		Vertex{Vector3{ 5.0f, 0.0f,  5.0f},  Vector3{ 0.0f, 1.0f, 0.0f},  Vector2{10.0f, 10.0f}},
		Vertex{Vector3{-5.0f, 0.0f,  5.0f},  Vector3{ 0.0f, 1.0f, 0.0f},  Vector2{ 0.0f, 10.0f}},
		Vertex{Vector3{-5.0f, 0.0f, -5.0f},  Vector3{ 0.0f, 1.0f, 0.0f},  Vector2{ 0.0f,  0.0f}}
	};
	meshPlane = std::make_shared<Mesh>(plane_vertices);

	modelCrate = std::make_shared<Model>();
	modelCrate->addMesh(meshCube, crateMat);

	modelGround = std::make_shared<Model>();
	modelGround->addMesh(meshPlane, groundMat);

	modelBullet = std::make_shared<Model>();
	modelBullet->addMesh(meshCube, bullet_mat);


	//  objects
	ground = std::make_shared<Object>();
	ground->addModel(modelGround);
	crate1 = std::make_shared<Object>();
	crate1->addModel(modelCrate);
	crate2 = std::make_shared<Object>();
	crate2->addModel(modelCrate);
	crate3 = std::make_shared<Object>();
	crate3->addModel(modelCrate);
	
	renderer->addObject(ground);
	renderer->addObject(crate1);
	renderer->addObject(crate2);
	renderer->addObject(crate3);

	ground->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	crate1->setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2->setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3->setPosition(Vector3{ -3.5f, 0.5f, -1.0f });


	//  player (camera)
	player = std::make_unique<Player>(1.5f, 5.0f, renderer_, modelBullet);
	currentCam = player->getCamera().lock();
	renderer->setCamera(player->getCamera());


	//  lights
	Vector3 dir_light{ 0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	renderer->addLight(std::make_shared<DirectionalLight>(Directionnal, Color::white, dir_light, 0.1f, 0.7f), Directionnal);
}

void FirstPersonScene::unload()
{
	meshCube->deleteObjects();
	meshPlane->deleteObjects();
	player->unload();
	litObjectShader->deleteProgram();
	bulletShader->deleteProgram();
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
