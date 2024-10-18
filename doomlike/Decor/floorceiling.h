#pragma once
#include <Objects/object.h>

#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>


class FloorObj : public Object
{
public:
	FloorObj() {}
	FloorObj(Vector3 position, bool isWood, bool hasCollision = true);

	void load() override;
	void setup(Vector3 position, bool isWood, bool hasCollision = true);
};


class Ceiling : public Object
{
public:
	Ceiling() {}
	Ceiling(Vector3 position, bool hasCollision = true);

	void load() override;
	void setup(Vector3 position, bool hasCollision = true);
};









// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace FloorCeilingSetup
{
	static void SetupFloorCeilings()
	{
		Renderer& renderer = Locator::getRenderer();

		AssetManager::LoadTexture("floor_diffuse", "pavement.jpg", false);

		AssetManager::LoadTexture("ceiling_diffuse", "doomlike/tex_woodceiling/woodceiling_basecolor.jpg", false);
		//AssetManager::LoadTexture("ceiling_specular", "doomlike/tex_woodceiling/woodceiling_roughness.jpg", GL_RED, false);

		AssetManager::LoadTexture("floor_wood_diffuse", "doomlike/tex_woodfloor/woodfloor_basecolor.jpg", false);
		AssetManager::LoadTexture("floor_wood_specular", "doomlike/tex_woodfloor/woodfloor_specular.jpg", false);

		Material& floor_mat = AssetManager::CreateMaterial("floor", AssetManager::GetShader("lit_object"));
		floor_mat.addTexture(&AssetManager::GetTexture("floor_diffuse"), TextureType::Diffuse);
		floor_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		floor_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		floor_mat.addParameter("material.shininess", 32.0f);
		floor_mat.addParameter("beta_prevent_tex_scaling", true);

		Material& floor_wood_mat = AssetManager::CreateMaterial("floor_wood", AssetManager::GetShader("lit_object"));
		floor_wood_mat.addTexture(&AssetManager::GetTexture("floor_wood_diffuse"), TextureType::Diffuse);
		floor_wood_mat.addTexture(&AssetManager::GetTexture("floor_wood_specular"), TextureType::Specular);
		floor_wood_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		floor_wood_mat.addParameter("material.shininess", 32.0f);
		floor_wood_mat.addParameter("beta_prevent_tex_scaling", true);

		Material& ceiling_mat = AssetManager::CreateMaterial("ceiling", AssetManager::GetShader("lit_object"));
		ceiling_mat.addTexture(&AssetManager::GetTexture("ceiling_diffuse"), TextureType::Diffuse);
		ceiling_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		ceiling_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		ceiling_mat.addParameter("material.shininess", 32.0f);
		ceiling_mat.addParameter("beta_prevent_tex_scaling", true);

		renderer.AddMaterial(&AssetManager::GetMaterial("floor"));
		renderer.AddMaterial(&AssetManager::GetMaterial("floor_wood"));
		renderer.AddMaterial(&AssetManager::GetMaterial("ceiling"));

		AssetManager::CreateModel("floor");
		AssetManager::GetModel("floor").addMesh(AssetManager::GetSingleMesh("default_plane"), AssetManager::GetMaterial("floor"));

		AssetManager::CreateModel("floor_wood");
		AssetManager::GetModel("floor_wood").addMesh(AssetManager::GetSingleMesh("default_plane"), AssetManager::GetMaterial("floor_wood"));

		AssetManager::CreateModel("ceiling");
		AssetManager::GetModel("ceiling").addMesh(AssetManager::GetSingleMesh("default_plane"), AssetManager::GetMaterial("ceiling"));
	}

	static void ReleaseFloorCeilings()
	{
		Renderer& renderer = Locator::getRenderer();

		renderer.RemoveMaterial(&AssetManager::GetMaterial("floor"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("floor_wood"));
		renderer.RemoveMaterial(&AssetManager::GetMaterial("ceiling"));
	}
};