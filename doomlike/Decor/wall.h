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
	void load() override;
	void setup(Vector3 position, FacingDirection facingDirection, bool hasCollision = true);
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

		rendererRef.addMaterial(&AssetManager::GetMaterial("wall"));


		std::vector<Vertex> wall_vertices  // constructed as a flat plane oriented towards positive Y for simplicity
		{
			// positions                           // normals                  // tex coords
			Vertex{Vector3{-1.25f, 0.0f, -1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}},
			Vertex{Vector3{ 1.25f, 0.0f, -1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 0.0f}},
			Vertex{Vector3{ 1.25f, 0.0f,  1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 2.0f}},
			Vertex{Vector3{ 1.25f, 0.0f,  1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 2.0f}},
			Vertex{Vector3{-1.25f, 0.0f,  1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 2.0f}},
			Vertex{Vector3{-1.25f, 0.0f, -1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}}
		};
		AssetManager::LoadSingleMesh("wall", wall_vertices);

		AssetManager::CreateModel("wall");
		AssetManager::GetModel("wall").addMesh(&AssetManager::GetSingleMesh("wall"), &AssetManager::GetMaterial("wall"));
	}


	static void ReleaseWalls(Renderer& rendererRef)
	{
		rendererRef.removeMaterial(&AssetManager::GetMaterial("wall"));
	}
};