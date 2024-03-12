#include "wall.h"
#include <Assets/assetManager.h>
#include <Rendering/renderer.h>







// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================


void Wall::SetupWalls(Renderer& rendererRef)
{
	AssetManager::LoadTexture("wall_diffuse", "doomlike/tex_stonewall/stonewall_basecolor.jpg", GL_RGB, false);
	AssetManager::LoadTexture("wall_specular", "doomlike/tex_stonewall/stonewall_specular.jpg", GL_RGB, false);

	Material& wall_mat = AssetManager::CreateMaterial("wall", &AssetManager::GetShader("lit_object"));
	wall_mat.addTexture(&AssetManager::GetTexture("wall_diffuse"), TextureType::Diffuse);
	wall_mat.addTexture(&AssetManager::GetTexture("wall_specular"), TextureType::Specular);
	wall_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	wall_mat.addParameter("material.shininess", 32.0f);

	rendererRef.addMaterial(&AssetManager::GetMaterial("wall"));


	std::vector<Vertex> wall_vertices
	{
		// positions                         // normals                  // tex coords
		Vertex{Vector3{-1.0f, 0.0f, -1.0f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}},
		Vertex{Vector3{ 1.0f, 0.0f, -1.0f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 0.0f}},
		Vertex{Vector3{ 1.0f, 0.0f,  1.0f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 2.0f}},
		Vertex{Vector3{ 1.0f, 0.0f,  1.0f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{2.0f, 2.0f}},
		Vertex{Vector3{-1.0f, 0.0f,  1.0f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 2.0f}},
		Vertex{Vector3{-1.0f, 0.0f, -1.0f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}}
	};
	AssetManager::LoadSingleMesh("wall", wall_vertices);

	AssetManager::CreateModel("wall");
	AssetManager::GetModel("wall").addMesh(&AssetManager::GetSingleMesh("wall"), &AssetManager::GetMaterial("wall"));
}

void Wall::ReleaseWalls(Renderer& rendererRef)
{
	rendererRef.removeMaterial(&AssetManager::GetMaterial("wall"));
}
