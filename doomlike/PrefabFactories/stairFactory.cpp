#include "stairFactory.h"
#include <Assets/assetManager.h>
#include <ECS/entityContainer.h>
#include <Rendering/modelRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <vector>


Entity* StairFactory::CreateStair(EntityContainer* entityContainer, StairFacingDirection facingDirection, const Vector3& position)
{
	Entity* stair_entity = entityContainer->createEntity();

	stair_entity->setPosition(position);
	stair_entity->setScale(0.0044f); //  this allows to have the stairs fitting in a 2*2*2 box

	Vector3 stairs_center; //  must be declared before the switch
	std::vector<Box> collisions_boxes;
	collisions_boxes.resize(7);

	switch (facingDirection)
	{
	case StairFacingDirection::StairFacingPositiveX:
		//  no need to rotate the stair entity
		
		stairs_center = Vector3{ 1.03f, 1.11f, -0.93f };
		for (int i = 0; i < 7; i++)
		{
			float num = float(i + 1);
			collisions_boxes[i] = Box{ stairs_center + Vector3{-0.125f * num, -1.125f + 0.250f * num, 0.0f}, Vector3{1.0f - 0.125f * num, 0.125f, 1.0f} };
		}
		break;

	case StairFacingDirection::StairFacingNegativeX:
		stair_entity->setRotation(Quaternion::fromEuler(Maths::toRadians(180.0f), 0.0f, 0.0f));

		stairs_center = Vector3{ -1.03f, 1.11f, 0.93f };
		for (int i = 0; i < 7; i++)
		{
			float num = float(i + 1);
			collisions_boxes[i] = Box{ stairs_center + Vector3{0.125f * num, -1.125f + 0.250f * num, 0.0f}, Vector3{1.0f - 0.125f * num, 0.125f, 1.0f} };
		}
		break;

	case StairFacingDirection::StairFacingPositiveZ:
		stair_entity->setRotation(Quaternion::fromEuler(Maths::toRadians(270.0f), 0.0f, 0.0f));

		stairs_center = Vector3{ 0.93f, 1.11f, 1.03f };
		for (int i = 0; i < 7; i++)
		{
			float num = float(i + 1);
			collisions_boxes[i] = Box{ stairs_center + Vector3{0.0f, -1.125f + 0.250f * num, -0.125f * num}, Vector3{1.0f, 0.125f, 1.0f - 0.125f * num} };
		}
		break;

	case StairFacingDirection::StairFacingNegativeZ:
		stair_entity->setRotation(Quaternion::fromEuler(Maths::toRadians(90.0f), 0.0f, 0.0f));

		stairs_center = Vector3{ -0.93f, 1.11f, -1.03f };
		for (int i = 0; i < 7; i++)
		{
			float num = float(i + 1);
			collisions_boxes[i] = Box{ stairs_center + Vector3{0.0f, -1.125f + 0.250f * num, 0.125f * num}, Vector3{1.0f, 0.125f, 1.0f - 0.125f * num} };
		}
		break;
	}

	stair_entity->addPositionRotated(Vector3{ 0.93f, -0.11f, -1.03f }); //  this allows to have the stairs otrigin at the center bottom

	stair_entity->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("stairs"));

	for (int i = 0; i < 7; i++)
	{
		std::shared_ptr<BoxAABBColComp> stair_step_col_comp = stair_entity->addComponentByClass<BoxAABBColComp>();
		stair_step_col_comp->setBox(collisions_boxes[i]);
		stair_step_col_comp->setCollisionChannel("solid");
		stair_step_col_comp->useOwnerScaleForBoxCenter = false;
		stair_step_col_comp->useOwnerScaleForBoxSize = false;
	}

	return stair_entity;
}



void StairFactory::SetupStairAssets()
{
	AssetManager::LoadTexture("stairs_diffuse", "doomlike/stairs/stairs_basecolor.png", false);

	Material& stairs_mat = AssetManager::CreateMaterial("stairs", AssetManager::GetShader("lit_object"));
	stairs_mat.addTexture(&AssetManager::GetTexture("stairs_diffuse"), TextureType::Diffuse);
	stairs_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Specular);
	stairs_mat.addTexture(&AssetManager::GetTexture("default_black"), TextureType::Emissive);
	stairs_mat.addParameter("material.shininess", 32.0f);
	//stairs_mat.addParameter("beta_prevent_tex_scaling", false);

	AssetManager::LoadMeshCollection("stairs", "doomlike/stairs/stairs.fbx");

	AssetManager::CreateModel("stairs");
	AssetManager::GetModel("stairs").addMeshes(AssetManager::GetMeshCollection("stairs"), AssetManager::GetMaterial("stairs"));
}

void StairFactory::ReleaseStairAssets()
{
	AssetManager::DeleteMaterial("stairs");
}