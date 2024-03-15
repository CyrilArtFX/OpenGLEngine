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

enum class WallSize : uint8_t
{
	WallSmall,
	WallBig
};


class Wall : public Object
{
public:
	Wall() {}
	Wall(Vector3 position, FacingDirection facingDirection, WallSize size, bool hasCollision = true);

	void load() override;
	void setup(Vector3 position, FacingDirection facingDirection, WallSize size, bool hasCollision = true);
};

//  TODO: a way to scale things like walls without scaling the texture (uvs would be scaled as well)







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


		std::vector<Vertex> wall_vertices_small  // constructed as a flat plane oriented towards positive Y for simplicity
		{
			// positions                           // normals                  // tex coords
			Vertex{Vector3{-1.25f, 0.0f, -1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}},
			Vertex{Vector3{ 1.25f, 0.0f, -1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 0.0f}},
			Vertex{Vector3{ 1.25f, 0.0f,  1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 2.0f}},
			Vertex{Vector3{ 1.25f, 0.0f,  1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 2.0f}},
			Vertex{Vector3{-1.25f, 0.0f,  1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 2.0f}},
			Vertex{Vector3{-1.25f, 0.0f, -1.25f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}}
		};
		AssetManager::LoadSingleMesh("wall_small", wall_vertices_small);

		std::vector<Vertex> wall_vertices_big  // constructed as a flat plane oriented towards positive Y for simplicity
		{
			// positions                           // normals                  // tex coords
			Vertex{Vector3{-2.5f, 0.0f, -2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}},
			Vertex{Vector3{ 2.5f, 0.0f, -2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{4.0f, 0.0f}},
			Vertex{Vector3{ 2.5f, 0.0f,  2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{4.0f, 4.0f}},
			Vertex{Vector3{ 2.5f, 0.0f,  2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{4.0f, 4.0f}},
			Vertex{Vector3{-2.5f, 0.0f,  2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 4.0f}},
			Vertex{Vector3{-2.5f, 0.0f, -2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}}
		};
		AssetManager::LoadSingleMesh("wall_big", wall_vertices_big);

		AssetManager::CreateModel("wall_small");
		AssetManager::GetModel("wall_small").addMesh(&AssetManager::GetSingleMesh("wall_small"), &AssetManager::GetMaterial("wall"));

		AssetManager::CreateModel("wall_big");
		AssetManager::GetModel("wall_big").addMesh(&AssetManager::GetSingleMesh("wall_big"), &AssetManager::GetMaterial("wall"));
	}


	static void ReleaseWalls(Renderer& rendererRef)
	{
		rendererRef.removeMaterial(&AssetManager::GetMaterial("wall"));
	}
};