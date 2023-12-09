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

	AssetManager::LoadTexture("crate_diffuse", "container2.png", TextureType::Diffuse, GL_RGBA, false);
	AssetManager::LoadTexture("crate_specular", "container2_specular.png", TextureType::Specular, GL_RGBA, false);
	AssetManager::LoadTexture("ground_diffuse", "pavement.jpg", TextureType::Diffuse, GL_RGB, false);
	AssetManager::LoadTexture("black_specular", "Default/black.png", TextureType::Specular, GL_RGBA, false);
	AssetManager::LoadTexture("black_emissive", "Default/black.png", TextureType::Emissive, GL_RGBA, false);
	AssetManager::LoadTexture("taxi_diffuse", "taxi/taxi_basecolor.png", TextureType::Diffuse, GL_RGBA, false);
	//AssetManager::LoadTexture("taxi_emissive", "taxi/taxi_emissive.png", TextureType::Emissive, GL_RGBA, false); //  just why does it crashes with this texture ??

	crateMat = std::make_shared<Material>(litObjectShader);
	crateMat->addTexture(&AssetManager::GetTexture("crate_diffuse"));
	crateMat->addTexture(&AssetManager::GetTexture("crate_specular"));
	crateMat->addTexture(&AssetManager::GetTexture("black_emissive"));
	crateMat->addParameter("material.shininess", 32.0f);

	groundMat = std::make_shared<Material>(litObjectShader);
	groundMat->addTexture(&AssetManager::GetTexture("ground_diffuse"));
	groundMat->addTexture(&AssetManager::GetTexture("black_specular"));
	groundMat->addTexture(&AssetManager::GetTexture("black_emissive"));
	groundMat->addParameter("material.shininess", 32.0f);

	taxiMat = std::make_shared<Material>(litObjectShader);
	taxiMat->addTexture(&AssetManager::GetTexture("taxi_diffuse"));
	taxiMat->addTexture(&AssetManager::GetTexture("black_specular"));
	taxiMat->addTexture(&AssetManager::GetTexture("black_emissive"));
	taxiMat->addParameter("material.shininess", 32.0f);

	std::shared_ptr<Material> bullet_mat = std::make_shared<Material>(bulletShader);
	bullet_mat->addParameter("emissive", 1.0f, 1.0f, 1.0f);

	renderer->addMaterial(crateMat);
	renderer->addMaterial(groundMat);
	renderer->addMaterial(bullet_mat);
	renderer->addMaterial(taxiMat);


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
	AssetManager::LoadSingleMesh("plane", plane_vertices);

	AssetManager::LoadMeshCollection("taxi", "taxi/taxi.fbx");

	AssetManager::CreateModel("crate");
	AssetManager::GetModel("crate").addMesh(&AssetManager::GetSingleMesh("cube"), crateMat);

	AssetManager::CreateModel("ground");
	AssetManager::GetModel("ground").addMesh(&AssetManager::GetSingleMesh("plane"), groundMat);

	AssetManager::CreateModel("bullet");
	AssetManager::GetModel("bullet").addMesh(&AssetManager::GetSingleMesh("cube"), bullet_mat);

	AssetManager::CreateModel("taxi");
	AssetManager::GetModel("taxi").addMeshes(&AssetManager::GetMeshCollection("taxi"), taxiMat);


	//  objects
	ground = std::make_shared<Object>();
	ground->addModel(&AssetManager::GetModel("ground"));
	crate1 = std::make_shared<Object>();
	crate1->addModel(&AssetManager::GetModel("crate"));
	crate2 = std::make_shared<Object>();
	crate2->addModel(&AssetManager::GetModel("crate"));
	crate3 = std::make_shared<Object>();
	crate3->addModel(&AssetManager::GetModel("crate"));
	testMesh = std::make_shared<Object>();
	testMesh->addModel(&AssetManager::GetModel("taxi"));
	
	renderer->addObject(ground);
	renderer->addObject(crate1);
	renderer->addObject(crate2);
	renderer->addObject(crate3);
	renderer->addObject(testMesh);

	ground->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	crate1->setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2->setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3->setPosition(Vector3{ -3.5f, 0.5f, -1.0f });
	testMesh->setPosition(Vector3{ -7.0f, 1.0f, 0.0f });
	testMesh->setScale(0.01f);
	testMesh->setRotation(Quaternion{ Vector3::unitX, Maths::toRadians(-90.0f) });


	//  player (camera)
	player = std::make_unique<Player>(1.5f, 5.0f, renderer_);
	currentCam = player->getCamera().lock();
	renderer->setCamera(player->getCamera());


	//  lights
	Vector3 dir_light{ 0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	renderer->addLight(std::make_shared<DirectionalLight>(Directionnal, Color::white, dir_light, 0.1f, 0.7f), Directionnal);
}

void FirstPersonScene::unload()
{
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
