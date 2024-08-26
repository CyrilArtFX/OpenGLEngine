#pragma once
#include <Objects/object.h>
#include <Objects/Lights/pointLight.h>

#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>

class Scene;


class Lamp : public Object
{
public:
	Lamp() {}
	Lamp(Vector3 position, bool isCeiling, Scene& sceneRef, float rand, bool startOff = false);

	void load() override;
	void setup(Vector3 position, bool isCeiling, Scene& sceneRef, float rand, bool startOff = false);

	void updateObject(float dt) override;
	void changeStatus(bool lightStatus);

private:
	PointLight light;

	bool isChandelier{ false };

	float time{ 0.0f };
	bool reverse{ false };
	float baseLightIntensity{ 0.0f };
};









// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace LampsSetup
{
	static void SetupLamps()
	{
		Renderer& renderer = Locator::getRenderer();

		AssetManager::LoadTexture("lamp_diffuse", "doomlike/lamp/lamp_basecolor.png", false);
		AssetManager::LoadTexture("lamp_specular", "doomlike/lamp/lamp_roughness.png", false);

		AssetManager::LoadTexture("chandelier_candle_diffuse", "doomlike/chandelier/ch_candles_basecolor.jpeg", false);
		AssetManager::LoadTexture("chandelier_base_diffuse", "doomlike/chandelier/ch_chandelier_basecolor.jpeg", false);
		AssetManager::LoadTexture("chandelier_base_specular", "doomlike/chandelier/ch_chandelier_roughness.jpeg", false);
		AssetManager::LoadTexture("chandelier_leather_diffuse", "doomlike/chandelier/ch_leather_basecolor.jpeg", false);
		AssetManager::LoadTexture("chandelier_leather_specular", "doomlike/chandelier/ch_leather_roughness.jpeg", false);

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

		Material& flame_off = AssetManager::CreateMaterial("flame_off", &AssetManager::GetShader("flat_emissive"));
		flame_off.addParameter("emissive", Color{ 20, 14 ,3, 255 });

		renderer.AddMaterial(&AssetManager::GetMaterial("lamp"));
		renderer.AddMaterial(&AssetManager::GetMaterial("chandelier_candle"));
		renderer.AddMaterial(&AssetManager::GetMaterial("chandelier_base"));
		renderer.AddMaterial(&AssetManager::GetMaterial("chandelier_leather"));
		renderer.AddMaterial(&AssetManager::GetMaterial("flame"));
		renderer.AddMaterial(&AssetManager::GetMaterial("flame_off"));

		AssetManager::LoadMeshCollection("lamp", "doomlike/lamp/lamp.fbx");
		AssetManager::LoadMeshCollection("chandelier", "doomlike/chandelier/chandelier.fbx");
		
		AssetManager::CreateMaterialCollection("lamp", MaterialCollection{ {&AssetManager::GetMaterial("lamp"), &AssetManager::GetMaterial("flame")} });
		AssetManager::CreateMaterialCollection("chandelier", MaterialCollection{ {
			&AssetManager::GetMaterial("chandelier_base"),
			&AssetManager::GetMaterial("chandelier_leather"),
			&AssetManager::GetMaterial("flame"), //  allows a better visibility than the candle material
			&AssetManager::GetMaterial("flame")} });

		Model& lamp = AssetManager::CreateModel("lamp");
		lamp.addMeshes(&AssetManager::GetMeshCollection("lamp"), &AssetManager::GetMaterialCollection("lamp"));

		Model& chandelier = AssetManager::CreateModel("chandelier");
		chandelier.addMeshes(&AssetManager::GetMeshCollection("chandelier"), &AssetManager::GetMaterialCollection("chandelier"));
	}


	static void ReleaseLamps()
	{
		Renderer& renderer = Locator::getRenderer();

		renderer.RemoveMaterial(&AssetManager::GetMaterial("lamp"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("chandelier_candle"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("chandelier_base"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("chandelier_leather"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("flame"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("flame_off"));
	}
};