#pragma once
#include <Objects/object.h>

#include <Assets/assetManager.h>
#include <Rendering/renderer.h>


namespace Stairs
{
	enum class FacingDirection : uint8_t
	{
		FacingPositiveX,
		FacingNegativeX,
		FacingPositiveZ,
		FacingNegativeZ
	};

	class StairsObj : public Object
	{
	public:
		StairsObj() {}
		StairsObj(Vector3 position, Stairs::FacingDirection facingDirection);

		void load() override;
		void setup(Vector3 position, Stairs::FacingDirection facingDirection);
	};
};












// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace StairsSetup
{
	static void SetupStairs(Renderer& rendererRef)
	{
		AssetManager::LoadTexture("stairs_diffuse", "doomlike/stairs/stairs_basecolor.png", GL_RGB, false);

		Material& stairs_mat = AssetManager::CreateMaterial("stairs", &AssetManager::GetShader("lit_object"));
		stairs_mat.addTexture(&AssetManager::GetTexture("stairs_diffuse"), TextureType::Diffuse);
		stairs_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		stairs_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		stairs_mat.addParameter("material.shininess", 32.0f);
		stairs_mat.addParameter("beta_prevent_tex_scaling", false);

		rendererRef.addMaterial(&AssetManager::GetMaterial("stairs"));

		AssetManager::LoadMeshCollection("stairs", "doomlike/stairs/stairs.fbx");

		AssetManager::CreateModel("stairs");
		AssetManager::GetModel("stairs").addMeshes(&AssetManager::GetMeshCollection("stairs"), &AssetManager::GetMaterial("stairs"));
	}


	static void ReleaseStairs(Renderer& rendererRef)
	{
		rendererRef.removeMaterial(&AssetManager::GetMaterial("stairs"));
	}
};
