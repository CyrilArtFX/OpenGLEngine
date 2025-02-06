#pragma once
#include <Objects/object.h>

#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>


namespace Wall
{
	enum class FacingDirection : uint8_t
	{
		FacingPositiveX,
		FacingNegativeX,
		FacingPositiveZ,
		FacingNegativeZ
	};

	class WallObj : public Object
	{
	public:
		WallObj() {}

		//  scale is a Vector2 because it corresponds to the plane scale once put flat
		WallObj(Vector3 position, Wall::FacingDirection facingDirection, Vector2 scale, bool hasCollision = true);

		void load() override;

		//  scale is a Vector2 because it corresponds to the plane scale once put flat
		void setup(Vector3 position, Wall::FacingDirection facingDirection, Vector2 scale, bool hasCollision = true);
	};
};












// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace WallSetup
{ 
	static void SetupWalls()
	{
		Renderer& renderer = Locator::getRenderer();

		AssetManager::LoadTexture("wall_diffuse", "doomlike/tex_stonewall/stonewall_basecolor.jpg", false);
		AssetManager::LoadTexture("wall_specular", "doomlike/tex_stonewall/stonewall_specular.jpg", false);

		Material& wall_mat = AssetManager::CreateMaterial("wall", AssetManager::GetShader("lit_object"));
		wall_mat.addTexture(&AssetManager::GetTexture("wall_diffuse"), TextureType::Diffuse);
		wall_mat.addTexture(&AssetManager::GetTexture("wall_specular"), TextureType::Specular);
		wall_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		wall_mat.addParameter("material.shininess", 32.0f);
		wall_mat.addParameter("beta_prevent_tex_scaling", true);

		AssetManager::CreateModel("wall");
		AssetManager::GetModel("wall").addMesh(AssetManager::GetSingleMesh("default_plane"), AssetManager::GetMaterial("wall"));
	}


	static void ReleaseWalls()
	{
		Renderer& renderer = Locator::getRenderer();

		AssetManager::DeleteMaterial("wall");
	}
};