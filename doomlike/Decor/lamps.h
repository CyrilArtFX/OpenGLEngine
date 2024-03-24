#pragma once
#include <Objects/object.h>
#include <Objects/Lights/pointLight.h>

#include <Assets/assetManager.h>
#include <Rendering/renderer.h>

class Scene;


class Lamp : public Object
{
public:
	Lamp() {}
	Lamp(Vector3 position, bool isCeiling, Scene& sceneRef, float rand);

	void load() override;
	void setup(Vector3 position, bool isCeiling, Scene& sceneRef, float rand);

	void updateObject(float dt) override;

private:
	PointLight light;

	float time{ 0.0f };
	bool reverse{ false };
	float baseLightIntensity{ 0.0f };
};









// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace LampsSetup
{
	static void SetupLamps(Renderer& rendererRef)
	{
		AssetManager::LoadTexture("lamp_diffuse", "doomlike/lamp/lamp_basecolor.png", GL_RGB, false);
		AssetManager::LoadTexture("lamp_specular", "doomlike/lamp/lamp_roughness.png", GL_RED, false);

		AssetManager::LoadTexture("chandelier_candle_diffuse", "doomlike/chandelier/ch_candles_basecolor.jpeg", GL_RGB, false);
		AssetManager::LoadTexture("chandelier_base_diffuse", "doomlike/chandelier/ch_chandelier_basecolor.jpeg", GL_RGB, false);
		AssetManager::LoadTexture("chandelier_base_specular", "doomlike/chandelier/ch_chandelier_roughness.jpeg", GL_RED, false);
		AssetManager::LoadTexture("chandelier_leather_diffuse", "doomlike/chandelier/ch_leather_basecolor.jpeg", GL_RGB, false);
		AssetManager::LoadTexture("chandelier_leather_specular", "doomlike/chandelier/ch_leather_roughness.jpeg", GL_RED, false);

		Material& lamp_mat = AssetManager::CreateMaterial("lamp", &AssetManager::GetShader("lit_object"));
		lamp_mat.addTexture(&AssetManager::GetTexture("lamp_diffuse"), TextureType::Diffuse);
		lamp_mat.addTexture(&AssetManager::GetTexture("lamp_specular"), TextureType::Specular);
		lamp_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		lamp_mat.addParameter("material.shininess", 32.0f);

		Material& chandelier_candle = AssetManager::CreateMaterial("chandelier_candle", &AssetManager::GetShader("lit_object"));
		chandelier_candle.addTexture(&AssetManager::GetTexture("chandelier_candle_diffuse"), TextureType::Diffuse);
		chandelier_candle.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		chandelier_candle.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		chandelier_candle.addParameter("material.shininess", 32.0f);
		Material& chandelier_base = AssetManager::CreateMaterial("chandelier_base", &AssetManager::GetShader("lit_object"));
		chandelier_base.addTexture(&AssetManager::GetTexture("chandelier_base_diffuse"), TextureType::Diffuse);
		chandelier_base.addTexture(&AssetManager::GetTexture("chandelier_base_specular"), TextureType::Specular);
		chandelier_base.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		chandelier_base.addParameter("material.shininess", 32.0f);
		Material& chandelier_leather = AssetManager::CreateMaterial("chandelier_leather", &AssetManager::GetShader("lit_object"));
		chandelier_leather.addTexture(&AssetManager::GetTexture("chandelier_leather_diffuse"), TextureType::Diffuse);
		chandelier_leather.addTexture(&AssetManager::GetTexture("chandelier_leather_specular"), TextureType::Specular);
		chandelier_leather.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		chandelier_leather.addParameter("material.shininess", 32.0f);

		Material& flame = AssetManager::CreateMaterial("flame", &AssetManager::GetShader("flat_emissive"));
		flame.addParameter("emissive", Color{ 209, 155, 67, 255 });

		rendererRef.addMaterial(&AssetManager::GetMaterial("lamp"));
		rendererRef.addMaterial(&AssetManager::GetMaterial("chandelier_candle"));
		rendererRef.addMaterial(&AssetManager::GetMaterial("chandelier_base"));
		rendererRef.addMaterial(&AssetManager::GetMaterial("chandelier_leather"));
		rendererRef.addMaterial(&AssetManager::GetMaterial("flame"));

		AssetManager::LoadMeshCollection("lamp", "doomlike/lamp/lamp.fbx");
		AssetManager::LoadMeshCollection("chandelier", "doomlike/chandelier/chandelier.fbx");

		Model& lamp = AssetManager::CreateModel("lamp");
		MeshCollection& lamp_meshes = AssetManager::GetMeshCollection("lamp");
		lamp.addMesh(&lamp_meshes.collection.at(0), &AssetManager::GetMaterial("lamp"));
		lamp.addMesh(&lamp_meshes.collection.at(1), &AssetManager::GetMaterial("flame"));

		Model& chandelier = AssetManager::CreateModel("chandelier");
		MeshCollection& chandelier_meshes = AssetManager::GetMeshCollection("chandelier");
		chandelier.addMesh(&chandelier_meshes.collection.at(0), &AssetManager::GetMaterial("chandelier_base"));
		chandelier.addMesh(&chandelier_meshes.collection.at(1), &AssetManager::GetMaterial("chandelier_base"));
		chandelier.addMesh(&chandelier_meshes.collection.at(2), &AssetManager::GetMaterial("chandelier_leather"));
		chandelier.addMesh(&chandelier_meshes.collection.at(3), &AssetManager::GetMaterial("flame")); //  allows a better visibility than the candle material
		chandelier.addMesh(&chandelier_meshes.collection.at(4), &AssetManager::GetMaterial("flame"));
	}


	static void ReleaseLamps(Renderer& rendererRef)
	{
		rendererRef.removeMaterial(&AssetManager::GetMaterial("lamp"));
		rendererRef.removeMaterial(&AssetManager::GetMaterial("chandelier_candle"));
		rendererRef.removeMaterial(&AssetManager::GetMaterial("chandelier_base"));
		rendererRef.removeMaterial(&AssetManager::GetMaterial("chandelier_leather"));
		rendererRef.removeMaterial(&AssetManager::GetMaterial("flame"));
	}
};