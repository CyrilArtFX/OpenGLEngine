#include "testFpsScene.h"

TestFpsScene::TestFpsScene()
{
}

void TestFpsScene::loadAssets()
{
	//  shaders, textures and materials
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", Lit);
	AssetManager::CreateShaderProgram("bullet", "Unlit/flat_emissive.vert", "Unlit/flat_emissive.frag", Unlit);

	AssetManager::LoadTexture("crate_diffuse", "container2.png", GL_RGBA, false);
	AssetManager::LoadTexture("crate_specular", "container2_specular.png", GL_RGBA, false);
	AssetManager::LoadTexture("ground_diffuse", "pavement.jpg", GL_RGB, false);
	AssetManager::LoadTexture("taxi_diffuse", "taxi/taxi_basecolor.png", GL_RGBA, false);
	AssetManager::LoadTexture("taxi_emissive", "taxi/taxi_emissive.png", GL_RGB, false);

	Material& crate_mat = AssetManager::CreateMaterial("crate", &AssetManager::GetShader("lit_object"));
	crate_mat.addTexture(&AssetManager::GetTexture("crate_diffuse"), TextureType::Diffuse);
	crate_mat.addTexture(&AssetManager::GetTexture("crate_specular"), TextureType::Specular);
	crate_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	crate_mat.addParameter("material.shininess", 32.0f);

	Material& ground_mat = AssetManager::CreateMaterial("ground", &AssetManager::GetShader("lit_object"));
	ground_mat.addTexture(&AssetManager::GetTexture("ground_diffuse"), TextureType::Diffuse);
	ground_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
	ground_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	ground_mat.addParameter("material.shininess", 32.0f);

	Material& taxi_mat = AssetManager::CreateMaterial("taxi", &AssetManager::GetShader("lit_object"));
	taxi_mat.addTexture(&AssetManager::GetTexture("taxi_diffuse"), TextureType::Diffuse);
	taxi_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
	taxi_mat.addTexture(&AssetManager::GetTexture("taxi_emissive"), TextureType::Emissive);
	taxi_mat.addParameter("material.shininess", 32.0f);

	Material& bullet_mat = AssetManager::CreateMaterial("bullet", &AssetManager::GetShader("bullet"));
	bullet_mat.addParameter("emissive", 1.0f, 1.0f, 1.0f);

	//  meshes and models
	AssetManager::LoadMeshCollection("taxi", "taxi/taxi.fbx");

	AssetManager::CreateModel("crate");
	AssetManager::GetModel("crate").addMesh(&AssetManager::GetSingleMesh("default_cube"), &AssetManager::GetMaterial("crate"));

	AssetManager::CreateModel("ground");
	AssetManager::GetModel("ground").addMesh(&AssetManager::GetSingleMesh("default_plane"), &AssetManager::GetMaterial("ground"));

	AssetManager::CreateModel("bullet");
	AssetManager::GetModel("bullet").addMesh(&AssetManager::GetSingleMesh("default_cube"), &AssetManager::GetMaterial("bullet"));

	AssetManager::CreateModel("taxi");
	AssetManager::GetModel("taxi").addMeshes(&AssetManager::GetMeshCollection("taxi"), &AssetManager::GetMaterial("taxi"));
}

void TestFpsScene::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });

	renderer->addMaterial(&AssetManager::GetMaterial("crate"));
	renderer->addMaterial(&AssetManager::GetMaterial("ground"));
	renderer->addMaterial(&AssetManager::GetMaterial("taxi"));
	renderer->addMaterial(&AssetManager::GetMaterial("bullet"));


	//  player (camera)
	player.setup(1.5f, 5.0f, renderer);
	currentCam = &player.getCamera();
	renderer->setCamera(&player.getCamera());


	//  objects
	ground.addModel(&AssetManager::GetModel("ground"));
	crate1.addModel(&AssetManager::GetModel("crate"));
	crate2.addModel(&AssetManager::GetModel("crate"));
	crate3.addModel(&AssetManager::GetModel("crate"));
	testMesh.addModel(&AssetManager::GetModel("taxi"));

	registerObject(&ground);
	registerObject(&crate1);
	registerObject(&crate2);
	registerObject(&crate3);
	registerObject(&testMesh);

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
	registerLight(&dirLight);
}

void TestFpsScene::unloadScene()
{
	player.unload();

	renderer->removeMaterial(&AssetManager::GetMaterial("crate"));
	renderer->removeMaterial(&AssetManager::GetMaterial("ground"));
	renderer->removeMaterial(&AssetManager::GetMaterial("taxi"));
	renderer->removeMaterial(&AssetManager::GetMaterial("bullet"));
}


void TestFpsScene::update(float dt)
{
	player.update(dt);
}
