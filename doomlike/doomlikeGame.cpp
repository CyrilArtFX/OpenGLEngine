#include "doomlikeGame.h"
#include <Assets/defaultAssets.h>
#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Inputs/Input.h>
#include <GameplayStatics/gameplayStatics.h>

#include <Decor/wall.h>
#include <Decor/floorceiling.h>
#include <Decor/stairs.h>
#include <Decor/lamps.h>

DoomlikeGame::DoomlikeGame()
{
}

void DoomlikeGame::loadGameAssets()
{
	Renderer& renderer = Locator::getRenderer();

	DefaultAssets::LoadDefaultAssets();

	//  shaders, textures and materials
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", Lit);

	AssetManager::LoadTexture("crate_diffuse", "container2.png", false);
	AssetManager::LoadTexture("crate_specular", "container2_specular.png", false);

	AssetManager::LoadTexture("taxi_diffuse", "taxi/taxi_basecolor.png", false);
	AssetManager::LoadTexture("taxi_emissive", "taxi/taxi_emissive.png", false);

	AssetManager::LoadTexture("enemy_diffuse", "doomlike/enemy/enemy_basecolor.jpeg", false);
	AssetManager::LoadTexture("enemy_specular", "doomlike/enemy/enemy_roughness.jpeg", false);
	AssetManager::LoadTexture("enemy_emissive", "doomlike/enemy/enemy_emissive.jpeg", false);

	AssetManager::LoadTexture("bullet_diffuse", "doomlike/bullet/bullet_basecolor.png", false);
	AssetManager::LoadTexture("bullet_specular", "doomlike/bullet/bullet_roughness.png", false);
	AssetManager::LoadTexture("bullet_emissive", "doomlike/bullet/bullet_emissive.png", false);

	AssetManager::LoadTexture("gun_diffuse", "doomlike/gun/gun_basecolor.png", false);
	AssetManager::LoadTexture("gun_specular", "doomlike/gun/gun_roughness.png", false);
	AssetManager::LoadTexture("gun_emissive", "doomlike/gun/gun_emissive.png", false);

	Material& crate_mat = AssetManager::CreateMaterial("crate", &AssetManager::GetShader("lit_object"));
	crate_mat.addTexture(&AssetManager::GetTexture("crate_diffuse"), TextureType::Diffuse);
	crate_mat.addTexture(&AssetManager::GetTexture("crate_specular"), TextureType::Specular);
	crate_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	crate_mat.addParameter("material.shininess", 32.0f);

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
	bullet_mat.addTexture(&AssetManager::GetTexture("bullet_emissive"), TextureType::Emissive);
	bullet_mat.addParameter("material.shininess", 32.0f);

	Material& gun_mat = AssetManager::CreateMaterial("gun", &AssetManager::GetShader("lit_object"));
	gun_mat.addTexture(&AssetManager::GetTexture("gun_diffuse"), TextureType::Diffuse);
	gun_mat.addTexture(&AssetManager::GetTexture("gun_specular"), TextureType::Specular);
	gun_mat.addTexture(&AssetManager::GetTexture("gun_emissive"), TextureType::Emissive);
	gun_mat.addParameter("material.shininess", 32.0f);

	renderer.AddMaterial(&AssetManager::GetMaterial("crate"));
	renderer.AddMaterial(&AssetManager::GetMaterial("taxi"));
	renderer.AddMaterial(&AssetManager::GetMaterial("gun"));
	renderer.AddMaterial(&AssetManager::GetMaterial("enemy"));
	renderer.AddMaterial(&AssetManager::GetMaterial("bullet"));
	renderer.AddMaterial(&AssetManager::GetMaterial("gun"));


	//  meshes and models
	AssetManager::LoadMeshCollection("taxi", "taxi/taxi.fbx");
	AssetManager::LoadMeshCollection("enemy", "doomlike/enemy/enemy.obj");
	AssetManager::LoadMeshCollection("bullet", "doomlike/bullet/bullet.fbx");
	AssetManager::LoadMeshCollection("gun", "doomlike/gun/gun.obj");

	AssetManager::CreateModel("crate");
	AssetManager::GetModel("crate").addMesh(&AssetManager::GetSingleMesh("default_cube"), &AssetManager::GetMaterial("crate"));

	AssetManager::CreateModel("taxi");
	AssetManager::GetModel("taxi").addMeshes(&AssetManager::GetMeshCollection("taxi"), &AssetManager::GetMaterial("taxi"));

	AssetManager::CreateModel("enemy");
	AssetManager::GetModel("enemy").addMeshes(&AssetManager::GetMeshCollection("enemy"), &AssetManager::GetMaterial("enemy"));

	AssetManager::CreateModel("bullet");
	AssetManager::GetModel("bullet").addMeshes(&AssetManager::GetMeshCollection("bullet"), &AssetManager::GetMaterial("bullet"));

	AssetManager::CreateModel("gun");
	AssetManager::GetModel("gun").addMeshes(&AssetManager::GetMeshCollection("gun"), &AssetManager::GetMaterial("gun"));


	//  decor setups
	WallSetup::SetupWalls();
	FloorCeilingSetup::SetupFloorCeilings();
	StairsSetup::SetupStairs();
	LampsSetup::SetupLamps();


	//  sounds
	AssetManager::CreateSound("feet1", "doomlike/sounds/foot_1.mp3", ACTIVATE_3D);
	AssetManager::CreateSound("feet2", "doomlike/sounds/foot_2.mp3", ACTIVATE_3D);
	AssetManager::CreateSound("shoot", "doomlike/sounds/shoot.mp3", 0);
	AudioSound& enemydeath_sound = AssetManager::CreateSound("enemydeath", "doomlike/sounds/enemy_death.mp3", ACTIVATE_3D);
	enemydeath_sound.setMinMaxDistance(1.0f, 20.0f);


	//  object channels
	CollisionChannels::RegisterTestChannel("PlayerEntity", { "solid", "enemy", "trigger_zone" }); //  for player and player bullets
	CollisionChannels::RegisterTestChannel("Enemy", { "solid", "player", "bullet" });
}

void DoomlikeGame::loadGame()
{
	player.setup(1.5f, 7.0f, 7.0f, 0.3f);
	Locator::getRenderer().SetCamera(&player.getCamera());

	loadLevel(2);
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

	if (Input::IsKeyPressed(GLFW_KEY_KP_2))
	{
		loadLevel(2);
	}

	if (Input::IsKeyPressed(GLFW_KEY_KP_3))
	{
		loadLevel(3);
	}
}

void DoomlikeGame::restartLevel()
{
	mustRestartLevel = true;
}

void DoomlikeGame::changeLevel(int levelIndex)
{
	if (levelIndex < 0 || levelIndex > 3)
	{
		std::cout << "DOOMLIKE ERROR: Tried to change the level with index to a level that doesn't exist.\n";
		return;
	}

	currentLevel = levelIndex;
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
		loadScene(&levelDebugScene);
		player.respawn(levelDebugScene);
		break;
	case 2:
		loadScene(&levelStartScene);
		player.respawn(levelStartScene);
		break;
	case 3:
		loadScene(&levelAdvancedScene);
		player.respawn(levelAdvancedScene);
		break;
	}
}

Camera& DoomlikeGame::getActiveCamera()
{
	return player.getCamera();
}


void DoomlikeGame::unloadGame()
{
	Renderer& renderer = Locator::getRenderer();

	player.unload();

	renderer.RemoveMaterial(&AssetManager::GetMaterial("crate"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("taxi"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("gun"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("enemy"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("bullet"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("gun"));

	WallSetup::ReleaseWalls();
	FloorCeilingSetup::ReleaseFloorCeilings();
	StairsSetup::ReleaseStairs();
	LampsSetup::ReleaseLamps();
}