#include "doomlikeLevelDebug.h"
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>

DoomlikeLevelDebug::DoomlikeLevelDebug()
{
}

void DoomlikeLevelDebug::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });


	//  objects
	ground1.addModel(&AssetManager::GetModel("ground"));
	ground2.addModel(&AssetManager::GetModel("ground"));
	ground3.addModel(&AssetManager::GetModel("ground"));
	crate1.addModel(&AssetManager::GetModel("crate"));
	crate2.addModel(&AssetManager::GetModel("crate"));
	crate3.addModel(&AssetManager::GetModel("crate"));
	crate4.addModel(&AssetManager::GetModel("crate"));
	stair1.addModel(&AssetManager::GetModel("crate"));
	stair2.addModel(&AssetManager::GetModel("crate"));
	movingPlatform1.addModel(&AssetManager::GetModel("crate"));
	movingPlatform2.addModel(&AssetManager::GetModel("crate"));

	registerObject(&ground1);
	registerObject(&ground2);
	registerObject(&ground3);
	registerObject(&crate1);
	registerObject(&crate2);
	registerObject(&crate3);
	registerObject(&crate4);
	registerObject(&stair1);
	registerObject(&stair2);
	registerObject(&movingPlatform1);
	registerObject(&movingPlatform2);
	Object& enemy_1 = registerObject(new Enemy()); //  better to add objects that can be altered like this

	ground1.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	ground2.setPosition(Vector3{ 0.0f, 0.0f, 10.0f });
	ground3.setPosition(Vector3{ 10.0f, 0.0f, 10.0f });
	crate1.setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2.setPosition(Vector3{ 3.0f, 1.0f, 13.0f });
	crate2.setScale(Vector3{ 0.5f, 2.0f, 2.0f });
	crate3.setPosition(Vector3{ 9.5f, 0.5f, 9.0f });
	crate4.setPosition(Vector3{ 2.5f, 3.0f, 7.5f });
	stair1.setScale(Vector3{ 1.0f, 0.2f, 1.0f });
	stair1.setPosition(Vector3{ 8.0f, 0.1f, 15.5f });
	stair2.setScale(Vector3{ 1.0f, 0.2f, 1.0f });
	stair2.setPosition(Vector3{ 9.0f, 0.3f, 15.5f });
	enemy_1.setPosition(Vector3{ -1.0f, 1.2f, 12.0f });

	movingPlatform1.setup(Vector3{ 10.0f, -3.0f, 2.0f }, Vector3{ 10.0f, 7.0f, 2.0f }, 5.0f);
	movingPlatform2.setup(Vector3{ 8.0f, 3.0f, 2.0f }, Vector3{ 3.0f, 3.0f, -2.0f }, 5.0f);


	//  collisions
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.5f, 0.0f}, Vector3{5.0f, 0.5f, 5.0f} }, &ground1, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.5f, 0.0f}, Vector3{5.0f, 0.5f, 5.0f} }, &ground2, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.5f, 0.0f}, Vector3{5.0f, 0.5f, 5.0f} }, &ground3, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate1, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate2, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate3, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate4, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, &stair1, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, &stair2, false, "solid"));


	//  lights
	Vector3 dir_light{ -0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	dirLight.load(Color::white, dir_light, 0.1f, 0.7f);
	registerLight(&dirLight);

	pointLight1.load(Color::red, Vector3{ 8.0f, 1.0f, 9.0f });
	registerLight(&pointLight1);


	//  spawn point
	spawnPosition = Vector3{ 8.0f, 0.0f, 9.0f };
	spawnRotation = Quaternion::fromEuler(Maths::toRadians(135.0f), 0.0f, 0.0f); //  not working for now, sadge
}

void DoomlikeLevelDebug::updateScene(float dt)
{
}

void DoomlikeLevelDebug::unloadScene()
{
}