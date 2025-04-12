#include "lampFactory.h"
#include <Assets/assetManager.h>
#include <ECS/entityContainer.h>
#include <GameComponents/lampComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Physics/AABB/boxAABBColComp.h>


Entity* LampFactory::CreateLamp(EntityContainer* entityContainer, const Vector3& position, float intensityMultiplier, bool isCeiling, bool startOff)
{
	Entity* lamp_entity = entityContainer->createEntity();

	std::string model_name;
	Vector3 light_comp_offset;
	float light_comp_diffuse;
	Box col_comp_box;

	if (isCeiling)
	{
		//  we must deal with models that are absolutely awful
		lamp_entity->setPosition(position + Vector3{ 0.0f, -2.0f, 0.0f });
		lamp_entity->setScale(0.001f);

		model_name = "chandelier";

		light_comp_offset = Vector3{ 0.0f, 0.7f, 0.0f };
		light_comp_diffuse = 0.41f;

		col_comp_box = Box{ Vector3{0.0f, 0.6f, 0.0f}, Vector3{0.5f, 0.5f, 0.5f} };
	}
	else
	{
		lamp_entity->setPosition(position + Vector3{ -2.58f, -1.23f, -1.52f });
		lamp_entity->setScale(0.012f);

		model_name = "lamp";

		light_comp_offset = Vector3{ 0.0f, 1.2f, 0.0f };
		light_comp_diffuse = 0.23f;

		col_comp_box = Box{ Vector3{2.58f, 1.87f, 1.52f}, Vector3{0.21f, 0.64f, 0.21f} };
	}


	std::shared_ptr<ModelRendererComponent> model_renderer_comp = lamp_entity->addComponentByClass<ModelRendererComponent>();
	model_renderer_comp->setModel(&AssetManager::GetModel(model_name));

	std::shared_ptr<PointLightComponent> light_comp = lamp_entity->addComponentByClass<PointLightComponent>();
	light_comp->setColor(Color{ 227, 141, 2, 225 });
	light_comp->setOffset(light_comp_offset);
	light_comp->setAmbientStrength(0.01f);
	light_comp->setDiffuseStrength(light_comp_diffuse * intensityMultiplier);
	light_comp->setUseDiffColorToSpecColor(true);

	std::shared_ptr<BoxAABBColComp> col_comp = lamp_entity->addComponentByClass<BoxAABBColComp>();
	col_comp->setBox(col_comp_box);
	col_comp->setCollisionChannel("solid");
	col_comp->useOwnerScaleForBoxCenter = false;
	col_comp->useOwnerScaleForBoxSize = false;

	std::shared_ptr<LampComponent> lamp_comp = lamp_entity->addComponentByClass<LampComponent>();
	lamp_comp->setup(light_comp, model_renderer_comp, isCeiling);
	lamp_comp->changeStatus(!startOff);

	return lamp_entity;
}

void LampFactory::SetupLampAssets()
{
	AssetManager::LoadTexture("lamp_diffuse", "doomlike/lamp/lamp_basecolor.png", false);
	AssetManager::LoadTexture("lamp_specular", "doomlike/lamp/lamp_roughness.png", false);

	AssetManager::LoadTexture("chandelier_candle_diffuse", "doomlike/chandelier/ch_candles_basecolor.jpeg", false);
	AssetManager::LoadTexture("chandelier_base_diffuse", "doomlike/chandelier/ch_chandelier_basecolor.jpeg", false);
	AssetManager::LoadTexture("chandelier_base_specular", "doomlike/chandelier/ch_chandelier_roughness.jpeg", false);
	AssetManager::LoadTexture("chandelier_leather_diffuse", "doomlike/chandelier/ch_leather_basecolor.jpeg", false);
	AssetManager::LoadTexture("chandelier_leather_specular", "doomlike/chandelier/ch_leather_roughness.jpeg", false);

	Material& lamp_mat = AssetManager::CreateMaterial("lamp", AssetManager::GetShader("lit_object"));
	lamp_mat.addTexture(&AssetManager::GetTexture("lamp_diffuse"), TextureType::Diffuse);
	lamp_mat.addTexture(&AssetManager::GetTexture("lamp_specular"), TextureType::Specular);
	lamp_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	lamp_mat.addParameter("material.shininess", 32.0f);

	Material& chandelier_candle = AssetManager::CreateMaterial("chandelier_candle", AssetManager::GetShader("lit_object"));
	chandelier_candle.addTexture(&AssetManager::GetTexture("chandelier_candle_diffuse"), TextureType::Diffuse);
	chandelier_candle.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
	chandelier_candle.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	chandelier_candle.addParameter("material.shininess", 32.0f);
	Material& chandelier_base = AssetManager::CreateMaterial("chandelier_base", AssetManager::GetShader("lit_object"));
	chandelier_base.addTexture(&AssetManager::GetTexture("chandelier_base_diffuse"), TextureType::Diffuse);
	chandelier_base.addTexture(&AssetManager::GetTexture("chandelier_base_specular"), TextureType::Specular);
	chandelier_base.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	chandelier_base.addParameter("material.shininess", 32.0f);
	Material& chandelier_leather = AssetManager::CreateMaterial("chandelier_leather", AssetManager::GetShader("lit_object"));
	chandelier_leather.addTexture(&AssetManager::GetTexture("chandelier_leather_diffuse"), TextureType::Diffuse);
	chandelier_leather.addTexture(&AssetManager::GetTexture("chandelier_leather_specular"), TextureType::Specular);
	chandelier_leather.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	chandelier_leather.addParameter("material.shininess", 32.0f);

	Material& flame = AssetManager::CreateMaterial("flame", AssetManager::GetShader("flat_emissive"));
	flame.addParameter("emissive", Color{ 209, 155, 67, 255 });

	Material& flame_off = AssetManager::CreateMaterial("flame_off", AssetManager::GetShader("flat_emissive"));
	flame_off.addParameter("emissive", Color{ 20, 14 ,3, 255 });

	AssetManager::LoadMeshCollection("lamp", "doomlike/lamp/lamp.fbx");
	AssetManager::LoadMeshCollection("chandelier", "doomlike/chandelier/chandelier.fbx");

	AssetManager::CreateMaterialCollection("lamp", { 
		&AssetManager::GetMaterial("lamp"), 
		&AssetManager::GetMaterial("flame") 
	});
	AssetManager::CreateMaterialCollection("chandelier", {
		&AssetManager::GetMaterial("chandelier_base"),
		&AssetManager::GetMaterial("chandelier_leather"),
		&AssetManager::GetMaterial("flame"), //  allows a better visibility than the candle material
		&AssetManager::GetMaterial("flame") 
	});

	Model& lamp = AssetManager::CreateModel("lamp");
	lamp.addMeshes(AssetManager::GetMeshCollection("lamp"), AssetManager::GetMaterialCollection("lamp"));

	Model& chandelier = AssetManager::CreateModel("chandelier");
	chandelier.addMeshes(AssetManager::GetMeshCollection("chandelier"), AssetManager::GetMaterialCollection("chandelier"));
}

void LampFactory::ReleaseLampAssets()
{
	AssetManager::DeleteMaterial("lamp");
	AssetManager::DeleteMaterial("chandelier_candle");
	AssetManager::DeleteMaterial("chandelier_base");
	AssetManager::DeleteMaterial("chandelier_leather");
	AssetManager::DeleteMaterial("flame");
	AssetManager::DeleteMaterial("flame_off");
}