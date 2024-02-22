#include "doomlikeGame.h"
#include <Assets/defaultAssets.h>
#include <Assets/assetManager.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Inputs/Input.h>
#include <GameplayStatics/gameplayStatics.h>

DoomlikeGame::DoomlikeGame()
{
}

void DoomlikeGame::loadGameAssets()
{
	DefaultAssets::LoadDefaultAssets(*renderer);

	//  shaders, textures and materials
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", Lit);

	AssetManager::LoadTexture("crate_diffuse", "container2.png", GL_RGBA, false);
	AssetManager::LoadTexture("crate_specular", "container2_specular.png", GL_RGBA, false);

	AssetManager::LoadTexture("ground_diffuse", "pavement.jpg", GL_RGB, false);

	AssetManager::LoadTexture("taxi_diffuse", "taxi/taxi_basecolor.png", GL_RGBA, false);
	AssetManager::LoadTexture("taxi_emissive", "taxi/taxi_emissive.png", GL_RGB, false);

	AssetManager::LoadTexture("enemy_diffuse", "doomlike/enemy/enemy_basecolor.jpeg", GL_RGB, false);
	AssetManager::LoadTexture("enemy_specular", "doomlike/enemy/enemy_roughness.jpeg", GL_RGB, false);
	AssetManager::LoadTexture("enemy_emissive", "doomlike/enemy/enemy_emissive.jpeg", GL_RGB, false);

	AssetManager::LoadTexture("bullet_diffuse", "doomlike/bullet/bullet_basecolor.png", GL_RGB, false);
	AssetManager::LoadTexture("bullet_specular", "doomlike/bullet/bullet_roughness.png", GL_RED, false); //  still need the system to automatically analyse texture color depth

	AssetManager::LoadTexture("gun_diffuse", "doomlike/gun/gun_basecolor.png", GL_RGBA, false);
	AssetManager::LoadTexture("gun_specular", "doomlike/gun/gun_roughness.png", GL_RGB16, false);
	AssetManager::LoadTexture("gun_emissive", "doomlike/gun/gun_emissive.png", GL_RED, false);

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

	Material& enemy_mat = AssetManager::CreateMaterial("enemy", &AssetManager::GetShader("lit_object"));
	enemy_mat.addTexture(&AssetManager::GetTexture("enemy_diffuse"), TextureType::Diffuse);
	enemy_mat.addTexture(&AssetManager::GetTexture("enemy_specular"), TextureType::Specular);
	enemy_mat.addTexture(&AssetManager::GetTexture("enemy_emissive"), TextureType::Emissive);
	enemy_mat.addParameter("material.shininess", 32.0f);

	Material& bullet_mat = AssetManager::CreateMaterial("bullet", &AssetManager::GetShader("lit_object"));
	bullet_mat.addTexture(&AssetManager::GetTexture("bullet_diffuse"), TextureType::Diffuse);
	bullet_mat.addTexture(&AssetManager::GetTexture("bullet_specular"), TextureType::Specular);
	bullet_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	bullet_mat.addParameter("material.shininess", 32.0f);

	Material& gun_mat = AssetManager::CreateMaterial("gun", &AssetManager::GetShader("lit_object"));
	gun_mat.addTexture(&AssetManager::GetTexture("gun_diffuse"), TextureType::Diffuse);
	gun_mat.addTexture(&AssetManager::GetTexture("gun_specular"), TextureType::Specular);
	gun_mat.addTexture(&AssetManager::GetTexture("gun_emissive"), TextureType::Emissive);
	gun_mat.addParameter("material.shininess", 32.0f);

	renderer->addMaterial(&AssetManager::GetMaterial("crate"));
	renderer->addMaterial(&AssetManager::GetMaterial("ground"));
	renderer->addMaterial(&AssetManager::GetMaterial("taxi"));
	renderer->addMaterial(&AssetManager::GetMaterial("gun"));
	renderer->addMaterial(&AssetManager::GetMaterial("enemy"));
	renderer->addMaterial(&AssetManager::GetMaterial("bullet"));
	renderer->addMaterial(&AssetManager::GetMaterial("gun"));


	//  meshes and models
	AssetManager::LoadMeshCollection("taxi", "taxi/taxi.fbx");
	AssetManager::LoadMeshCollection("enemy", "doomlike/enemy/enemy.obj");
	AssetManager::LoadMeshCollection("bullet", "doomlike/bullet/bullet.fbx");
	AssetManager::LoadMeshCollection("gun", "doomlike/gun/gun.obj");

	AssetManager::CreateModel("crate");
	AssetManager::GetModel("crate").addMesh(&AssetManager::GetSingleMesh("default_cube"), &AssetManager::GetMaterial("crate"));

	AssetManager::CreateModel("ground");
	AssetManager::GetModel("ground").addMesh(&AssetManager::GetSingleMesh("default_plane"), &AssetManager::GetMaterial("ground"));

	AssetManager::CreateModel("taxi");
	AssetManager::GetModel("taxi").addMeshes(&AssetManager::GetMeshCollection("taxi"), &AssetManager::GetMaterial("taxi"));

	AssetManager::CreateModel("enemy");
	AssetManager::GetModel("enemy").addMeshes(&AssetManager::GetMeshCollection("enemy"), &AssetManager::GetMaterial("enemy"));

	AssetManager::CreateModel("bullet");
	AssetManager::GetModel("bullet").addMeshes(&AssetManager::GetMeshCollection("bullet"), &AssetManager::GetMaterial("bullet"));

	AssetManager::CreateModel("gun");
	AssetManager::GetModel("gun").addMeshes(&AssetManager::GetMeshCollection("gun"), &AssetManager::GetMaterial("gun"));


	//  object channels
	CollisionChannels::RegisterTestChannel("PlayerEntity", { "solid", "enemy"}); //  for player and player bullets
	CollisionChannels::RegisterTestChannel("Enemy", { "player", "bullet" });
}

void DoomlikeGame::loadGame()
{
	player.setup(1.5f, 7.0f, 10.0f, 0.3f, renderer);
	renderer->setCamera(&player.getCamera());

	loadLevel(1);
}


void DoomlikeGame::updateGame(float dt)
{
	if (mustRestartLevel)
	{
		loadLevel(currentLevel);
		mustRestartLevel = false;
	}

	player.update(dt);

	if (Input::IsKeyPressed(GLFW_KEY_KP_0))
	{
		loadLevel(0);
	}

	if (Input::IsKeyPressed(GLFW_KEY_KP_1))
	{
		loadLevel(1);
	}
}

void DoomlikeGame::restartLevel()
{
	mustRestartLevel = true;
}

void DoomlikeGame::loadLevel(int index)
{
	currentLevel = index;
	switch (index)
	{
	case 0:
		loadScene(&testScene);
		player.respawn(testScene);
		break;
	case 1:
		loadScene(&levelOneScene);
		player.respawn(levelOneScene);
		break;
	}
}

Camera& DoomlikeGame::getActiveCamera()
{
	return player.getCamera();
}


void DoomlikeGame::unloadGame()
{
	player.unload();

	renderer->removeMaterial(&AssetManager::GetMaterial("crate"));
	renderer->removeMaterial(&AssetManager::GetMaterial("ground"));
	renderer->removeMaterial(&AssetManager::GetMaterial("taxi"));
	renderer->removeMaterial(&AssetManager::GetMaterial("gun"));
	renderer->removeMaterial(&AssetManager::GetMaterial("enemy"));
	renderer->removeMaterial(&AssetManager::GetMaterial("bullet"));
	renderer->removeMaterial(&AssetManager::GetMaterial("gun"));
}