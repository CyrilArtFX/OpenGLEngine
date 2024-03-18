#pragma once
#include <Objects/object.h>

#include <Assets/assetManager.h>
#include <Rendering/renderer.h>


enum class FacingDirection : uint8_t
{
	FacingPositiveX,
	FacingNegativeX,
	FacingPositiveZ,
	FacingNegativeZ
};


class Wall : public Object
{
public:
	Wall() {}

	//  scale is a Vector2 because it corresponds to the plane scale once put flat
	Wall(Vector3 position, FacingDirection facingDirection, Vector2 scale, bool hasCollision = true);

	void load() override;

	//  scale is a Vector2 because it corresponds to the plane scale once put flat
	void setup(Vector3 position, FacingDirection facingDirection, Vector2 scale, bool hasCollision = true);
};









// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace WallSetup
{ 
	static void SetupWalls(Renderer& rendererRef)
	{
		AssetManager::LoadTexture("wall_diffuse", "doomlike/tex_stonewall/stonewall_basecolor.jpg", GL_RGB, false);
		AssetManager::LoadTexture("wall_specular", "doomlike/tex_stonewall/stonewall_specular.jpg", GL_RGB, false);

		Material& wall_mat = AssetManager::CreateMaterial("wall", &AssetManager::GetShader("lit_object"));
		wall_mat.addTexture(&AssetManager::GetTexture("wall_diffuse"), TextureType::Diffuse);
		wall_mat.addTexture(&AssetManager::GetTexture("wall_specular"), TextureType::Specular);
		wall_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		wall_mat.addParameter("material.shininess", 32.0f);
		wall_mat.addParameter("beta_prevent_tex_scaling", true);

		rendererRef.addMaterial(&AssetManager::GetMaterial("wall"));

		AssetManager::CreateModel("wall");
		AssetManager::GetModel("wall").addMesh(&AssetManager::GetSingleMesh("default_plane"), &AssetManager::GetMaterial("wall"));
	}


	static void ReleaseWalls(Renderer& rendererRef)
	{
		rendererRef.removeMaterial(&AssetManager::GetMaterial("wall"));
	}
};