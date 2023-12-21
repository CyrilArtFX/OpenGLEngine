#include "expositionGame.h"
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
	DefaultAssets::LoadDefaultAssets();

	//  shaders, textures and materials
	AssetManager::CreateShaderProgram("lit_object", "Lit/object_lit.vert", "Lit/object_lit.frag", ShaderType::Lit);
	AssetManager::CreateShaderProgram("flat_emissive", "Unlit/flat_emissive.vert", "Unlit/flat_emissive.frag", ShaderType::Unlit);

	AssetManager::LoadTexture("container_diffuse", "container2.png", GL_RGBA, false);
	AssetManager::LoadTexture("container_specular", "container2_specular.png", GL_RGBA, false);
	AssetManager::LoadTexture("container_emissive", "matrix.jpg", GL_RGB, false);

	Material& container_mat = AssetManager::CreateMaterial("container", &AssetManager::GetShader("lit_object"));
	container_mat.addTexture(&AssetManager::GetTexture("container_diffuse"), TextureType::Diffuse);
	container_mat.addTexture(&AssetManager::GetTexture("container_specular"), TextureType::Specular);
	container_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	container_mat.addParameter("material.shininess", 32.0f);

	Material& light_source_mat = AssetManager::CreateMaterial("light_source", &AssetManager::GetShader("flat_emissive"));
	light_source_mat.addParameter("emissive", 1.0f, 1.0f, 1.0f);

	renderer->addMaterial(&AssetManager::GetMaterial("container"));
	renderer->addMaterial(&AssetManager::GetMaterial("light_source"));


	//  models 
	AssetManager::CreateModel("container");
	AssetManager::GetModel("container").addMesh(&AssetManager::GetSingleMesh("default_cube"), &AssetManager::GetMaterial("container"));

	AssetManager::CreateModel("light_cube");
	AssetManager::GetModel("light_cube").addMesh(&AssetManager::GetSingleMesh("default_cube"), &AssetManager::GetMaterial("light_source"));
}

void ExpositionGame::loadGame()
{
	loadScene(&expositionScene);
}


void ExpositionGame::unloadGame()
{
	renderer->removeMaterial(&AssetManager::GetMaterial("container"));
	renderer->removeMaterial(&AssetManager::GetMaterial("light_source"));
}