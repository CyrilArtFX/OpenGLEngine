#include "lamps.h"
#include <Core/scene.h>
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>

Lamp::Lamp(Vector3 position, bool isCeiling, Scene& sceneRef, float rand)
{
	setup(position, isCeiling, sceneRef, rand);
}

void Lamp::load()
{
}

void Lamp::setup(Vector3 position, bool isCeiling, Scene& sceneRef, float rand)
{
	if (isCeiling)
	{
		addModel(&AssetManager::GetModel("chandelier"));
		setPosition(position + Vector3{0.0f, -2.0f, 0.0f});
		setScale(0.001f);

		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.6f, 0.0f}, Vector3{0.5f, 0.5f, 0.5f} }, this, false, "solid", false, false));

		light.load(Color{ 227, 141, 2, 255 }, position + Vector3{ 0.0f, 0.7f, 0.0f }, 0.01f, 0.41f);
		baseLightIntensity = 0.4f;
	}
	else
	{
		addModel(&AssetManager::GetModel("lamp"));
		setPosition(position + Vector3{ -2.58f, -1.23f, -1.52f });
		setScale(0.012f);

		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{2.58f, 1.87f, 1.52f}, Vector3{0.21f, 0.64f, 0.21f} }, this, false, "solid", false, false));

		light.load(Color{ 227, 141, 2, 255 }, position + Vector3{ 0.0f, 1.2f, 0.0f }, 0.01f, 0.23f);
		baseLightIntensity = 0.22f;
	}

	
	light.setUseDiffColorToSpecColor(true);

	sceneRef.registerLight(&light);
	time = rand;
}

void Lamp::updateObject(float dt)
{
	if (reverse)
	{
		time -= dt;
		if (time < 0.0f) reverse = false;
	}
	else
	{
		time += dt;
		if (time > 1.0f) reverse = true;
	}

	light.setDiffuseStrength(baseLightIntensity + (Maths::sin(time) / 11.0f));
}