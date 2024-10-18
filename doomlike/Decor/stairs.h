#pragma once
#include <Objects/object.h>

#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>


namespace Stairs
{
	enum class FacingDirection : uint8_t
	{
		FacingPositiveX,
		FacingNegativeX,
		FacingPositiveZ,
		FacingNegativeZ
	};


	/*
	* Stairs have the size of a 2*2*2 box.
	* Origin is at the center bottom.
	* Steps height is 0.25f.
	*/
	class StairsObj : public Object
	{
	public:
		StairsObj() {}

		//  position correspond to the center bottom of the stairs
		StairsObj(Vector3 position, Stairs::FacingDirection facingDirection);

		void load() override;

		//  position correspond to the center bottom of the stairs
		void setup(Vector3 position, Stairs::FacingDirection facingDirection);
	};
};












// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace StairsSetup
{
	static void SetupStairs()
	{
		Renderer& renderer = Locator::getRenderer();

		AssetManager::LoadTexture("stairs_diffuse", "doomlike/stairs/stairs_basecolor.png", false);

		Material& stairs_mat = AssetManager::CreateMaterial("stairs", AssetManager::GetShader("lit_object"));
		stairs_mat.addTexture(&AssetManager::GetTexture("stairs_diffuse"), TextureType::Diffuse);
		stairs_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		stairs_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		stairs_mat.addParameter("material.shininess", 32.0f);
		//stairs_mat.addParameter("beta_prevent_tex_scaling", false);

		renderer.AddMaterial(&AssetManager::GetMaterial("stairs"));

		AssetManager::LoadMeshCollection("stairs", "doomlike/stairs/stairs.fbx");

		AssetManager::CreateModel("stairs");
		AssetManager::GetModel("stairs").addMeshes(AssetManager::GetMeshCollection("stairs"), AssetManager::GetMaterial("stairs"));
	}


	static void ReleaseStairs()
	{
		Renderer& renderer = Locator::getRenderer();

		renderer.RemoveMaterial(&AssetManager::GetMaterial("stairs"));
	}
};
