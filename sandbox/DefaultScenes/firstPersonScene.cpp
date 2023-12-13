#include "firstPersonScene.h"

FirstPersonScene::FirstPersonScene() : Scene()
{
}


void FirstPersonScene::load(std::weak_ptr<Renderer> renderer_)
{
	renderer = renderer_.lock();

	//  player (camera)
	player = std::make_unique<Player>(1.5f, 5.0f, renderer_); 
	currentCam = player->getCamera().lock(); 
	renderer->setCamera(player->getCamera());


	//  shaders, textures and materials
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", Lit);
	AssetManager::CreateShaderProgram("bullet", "Unlit/flat_emissive.vert", "Unlit/flat_emissive.frag", Unlit);

	AssetManager::LoadTexture("crate_diffuse", "container2.png", TextureType::Diffuse, GL_RGBA, false);
	AssetManager::LoadTexture("crate_specular", "container2_specular.png", TextureType::Specular, GL_RGBA, false);
	AssetManager::LoadTexture("ground_diffuse", "pavement.jpg", TextureType::Diffuse, GL_RGB, false);
	AssetManager::LoadTexture("black_specular", "Default/black.png", TextureType::Specular, GL_RGBA, false);
	AssetManager::LoadTexture("black_emissive", "Default/black.png", TextureType::Emissive, GL_RGBA, false);
	AssetManager::LoadTexture("taxi_diffuse", "taxi/taxi_basecolor.png", TextureType::Diffuse, GL_RGBA, false);
	AssetManager::LoadTexture("taxi_emissive", "taxi/taxi_emissive.png", TextureType::Emissive, GL_RGB, false);

	Material& crate_mat = AssetManager::CreateMaterial("crate", &AssetManager::GetShader("lit_object"));
	crate_mat.addTexture(&AssetManager::GetTexture("crate_diffuse")); 
	crate_mat.addTexture(&AssetManager::GetTexture("crate_specular")); 
	crate_mat.addTexture(&AssetManager::GetTexture("black_emissive")); 
	crate_mat.addParameter("material.shininess", 32.0f); 

	Material& ground_mat = AssetManager::CreateMaterial("ground", &AssetManager::GetShader("lit_object")); 
	ground_mat.addTexture(&AssetManager::GetTexture("ground_diffuse"));
	ground_mat.addTexture(&AssetManager::GetTexture("black_specular"));
	ground_mat.addTexture(&AssetManager::GetTexture("black_emissive"));
	ground_mat.addParameter("material.shininess", 32.0f);

	Material& taxi_mat = AssetManager::CreateMaterial("taxi", &AssetManager::GetShader("lit_object")); 
	taxi_mat.addTexture(&AssetManager::GetTexture("taxi_diffuse"));
	taxi_mat.addTexture(&AssetManager::GetTexture("black_specular"));
	taxi_mat.addTexture(&AssetManager::GetTexture("taxi_emissive")); 
	taxi_mat.addParameter("material.shininess", 32.0f); 

	Material& bullet_mat = AssetManager::CreateMaterial("bullet", &AssetManager::GetShader("bullet"));
	bullet_mat.addParameter("emissive", 1.0f, 1.0f, 1.0f); 

	renderer->addMaterial(&AssetManager::GetMaterial("crate"));
	renderer->addMaterial(&AssetManager::GetMaterial("ground"));
	renderer->addMaterial(&AssetManager::GetMaterial("taxi"));
	renderer->addMaterial(&AssetManager::GetMaterial("bullet"));


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
	AssetManager::GetModel("crate").addMesh(&AssetManager::GetSingleMesh("cube"), &AssetManager::GetMaterial("crate")); 

	AssetManager::CreateModel("ground");
	AssetManager::GetModel("ground").addMesh(&AssetManager::GetSingleMesh("plane"), &AssetManager::GetMaterial("ground"));

	AssetManager::CreateModel("bullet");
	AssetManager::GetModel("bullet").addMesh(&AssetManager::GetSingleMesh("cube"), &AssetManager::GetMaterial("bullet"));

	AssetManager::CreateModel("taxi");
	AssetManager::GetModel("taxi").addMeshes(&AssetManager::GetMeshCollection("taxi"), &AssetManager::GetMaterial("taxi"));


	//  objects
	ground.addModel(&AssetManager::GetModel("ground"));
	crate1.addModel(&AssetManager::GetModel("crate"));
	crate2.addModel(&AssetManager::GetModel("crate"));
	crate3.addModel(&AssetManager::GetModel("crate"));
	testMesh.addModel(&AssetManager::GetModel("taxi"));
	
	renderer->addObject(&ground);
	renderer->addObject(&crate1);
	renderer->addObject(&crate2);
	renderer->addObject(&crate3);
	renderer->addObject(&testMesh);

	ground.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	crate1.setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2.setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3.setPosition(Vector3{ -3.5f, 0.5f, -1.0f });
	testMesh.setPosition(Vector3{ -7.0f, 1.0f, 0.0f });
	testMesh.setScale(0.01f);
	testMesh.setRotation(Quaternion{ Vector3::unitX, Maths::toRadians(-90.0f) });


	//  lights
	Vector3 dir_light{ 0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	dirLight.load(Color::white, dir_light, 0.1f, 0.7f);
	renderer->addLight(&dirLight);
}

void FirstPersonScene::unload()
{
	player->unload();
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
