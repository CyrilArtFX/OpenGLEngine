#pragma once
#include <Objects/object.h>

#include <Assets/assetManager.h>
#include <Rendering/renderer.h>


class FloorObj : public Object
{
public:
	void load() override;
	void setup(Vector3 position, bool hasCollision = true);
};


class Ceiling : public Object
{
public:
	void load() override;
	void setup(Vector3 position, bool hasCollision = true);
};









// ============================================================================
//  ---------------- Compact setup for code clarity --------------------------
// ============================================================================

namespace FloorCeilingSetup
{
	static void SetupFloorCeilings(Renderer& rendererRef)
	{
		AssetManager::LoadTexture("floor_diffuse", "pavement.jpg", GL_RGB, false);

		AssetManager::LoadTexture("ceiling_diffuse", "doomlike/tex_woodceiling/woodceiling_basecolor.jpg", GL_RGB, false);
		//AssetManager::LoadTexture("ceiling_specular", "doomlike/tex_woodceiling/woodceiling_roughness.jpg", GL_RED, false);

		Material& floor_mat = AssetManager::CreateMaterial("floor", &AssetManager::GetShader("lit_object"));
		floor_mat.addTexture(&AssetManager::GetTexture("floor_diffuse"), TextureType::Diffuse);
		floor_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		floor_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		floor_mat.addParameter("material.shininess", 32.0f);

		Material& ceiling_mat = AssetManager::CreateMaterial("ceiling", &AssetManager::GetShader("lit_object"));
		ceiling_mat.addTexture(&AssetManager::GetTexture("ceiling_diffuse"), TextureType::Diffuse);
		ceiling_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
		ceiling_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
		ceiling_mat.addParameter("material.shininess", 32.0f);

		rendererRef.addMaterial(&AssetManager::GetMaterial("floor"));
		rendererRef.addMaterial(&AssetManager::GetMaterial("ceiling"));


		std::vector<Vertex> floorceiling_vertices
		{
			// positions                         // normals                  // tex coords
			Vertex{Vector3{-2.5f, 0.0f, -2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}},
			Vertex{Vector3{ 2.5f, 0.0f, -2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{5.0f, 0.0f}},
			Vertex{Vector3{ 2.5f, 0.0f,  2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{5.0f, 5.0f}},
			Vertex{Vector3{ 2.5f, 0.0f,  2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{5.0f, 5.0f}},
			Vertex{Vector3{-2.5f, 0.0f,  2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 5.0f}},
			Vertex{Vector3{-2.5f, 0.0f, -2.5f},  Vector3{0.0f, 1.0f, 0.0f},  Vector2{0.0f, 0.0f}}
		};
		AssetManager::LoadSingleMesh("floorceiling", floorceiling_vertices);

		AssetManager::CreateModel("floor");
		AssetManager::GetModel("floor").addMesh(&AssetManager::GetSingleMesh("floorceiling"), &AssetManager::GetMaterial("floor"));

		AssetManager::CreateModel("ceiling");
		AssetManager::GetModel("ceiling").addMesh(&AssetManager::GetSingleMesh("floorceiling"), &AssetManager::GetMaterial("ceiling"));
	}

	static void ReleaseFloorCeilings(Renderer& rendererRef)
	{
		rendererRef.removeMaterial(&AssetManager::GetMaterial("floor"));
		rendererRef.removeMaterial(&AssetManager::GetMaterial("ceiling"));
	}
};