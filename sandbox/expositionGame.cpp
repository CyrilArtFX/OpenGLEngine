#include "expositionGame.h"
#include <ServiceLocator/locator.h>
#include <Assets/defaultAssets.h>
#include <Assets/assetManager.h>

ExpositionGame::ExpositionGame()
{
}

void ExpositionGame::updateGame(float dt)
{
}


void ExpositionGame::loadGameAssets()
{
	Renderer& renderer = Locator::getRenderer();

	DefaultAssets::LoadDefaultAssets();

	//  shaders, textures and materials
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", ShaderType::Lit);

	AssetManager::LoadTexture("container_diffuse", "container2.png", false);
	AssetManager::LoadTexture("container_specular", "container2_specular.png", false);
	AssetManager::LoadTexture("container_emissive", "matrix.jpg", false);

	AssetManager::LoadTexture("backpack_diffuse", "backpack/backpack_basecolor.jpg", false);
	AssetManager::LoadTexture("backpack_specular", "backpack/backpack_specular.jpg", false);

	AssetManager::LoadTexture("smileyface_sprite", "awesomeface.png", false);

	Material& container_mat = AssetManager::CreateMaterial("container", AssetManager::GetShader("lit_object"));
	container_mat.addTexture(&AssetManager::GetTexture("container_diffuse"), TextureType::Diffuse);
	container_mat.addTexture(&AssetManager::GetTexture("container_specular"), TextureType::Specular);
	container_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	container_mat.addParameter("material.shininess", 32.0f);

	Material& backpack_mat = AssetManager::CreateMaterial("backpack", AssetManager::GetShader("lit_object"));
	backpack_mat.addTexture(&AssetManager::GetTexture("backpack_diffuse"), TextureType::Diffuse);
	backpack_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
	backpack_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	backpack_mat.addParameter("material.shininess", 32.0f);

	Material& light_source_mat_white = AssetManager::CreateMaterial("light_source_white", AssetManager::GetShader("flat_emissive"));
	light_source_mat_white.addParameter("emissive", Color::white.toVector());

	Material& light_source_mat_cyan = AssetManager::CreateMaterial("light_source_cyan", AssetManager::GetShader("flat_emissive"));
	light_source_mat_cyan.addParameter("emissive", Color::cyan.toVector());

	renderer.AddMaterial(&AssetManager::GetMaterial("container"));
	renderer.AddMaterial(&AssetManager::GetMaterial("light_source_white"));
	renderer.AddMaterial(&AssetManager::GetMaterial("light_source_cyan"));
	renderer.AddMaterial(&AssetManager::GetMaterial("backpack"));


	//  models 
	AssetManager::CreateModel("container").addMesh(AssetManager::GetSingleMesh("default_cube"), AssetManager::GetMaterial("container"));

	AssetManager::CreateModel("light_cube_white").addMesh(AssetManager::GetSingleMesh("default_cube"), AssetManager::GetMaterial("light_source_white"));
	AssetManager::CreateModel("light_cube_cyan").addMesh(AssetManager::GetSingleMesh("default_cube"), AssetManager::GetMaterial("light_source_cyan"));

	AssetManager::LoadMeshCollection("backpack", "backpack/backpack.fbx");
	AssetManager::CreateModel("backpack").addMeshes(AssetManager::GetMeshCollection("backpack"), AssetManager::GetMaterial("backpack"));


	//  audio
	AssetManager::CreateSound("sound", "fartreverb.mp3", ACTIVATE_LOOP);
	AudioSound& music = AssetManager::CreateSound("music", "TestMusic.mp3", ACTIVATE_3D | ACTIVATE_STREAM);
	music.setMinMaxDistance(50.0f, 100.0f);
}

void ExpositionGame::loadGame()
{
	test_game_entity = createEntity();

	loadScene(&expositionScene);
}


void ExpositionGame::unloadGame()
{
	Renderer& renderer = Locator::getRenderer();

	renderer.RemoveMaterial(&AssetManager::GetMaterial("container"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("light_source_white"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("light_source_cyan"));
	renderer.RemoveMaterial(&AssetManager::GetMaterial("backpack"));
}