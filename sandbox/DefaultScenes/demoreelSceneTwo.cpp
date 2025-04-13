#include "demoreelSceneTwo.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>
#include <Inputs/Input.h>

#include <Rendering/cameraComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Rendering/Lights/directionalLightComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>


const Vector3 CAMERA_TARGET = Vector3{0.0f, 1.0f, 0.0f};
const float CAMERA_HEIGHT = 8.0f;

void DemoreelSceneTwo::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 0, 5, 20, 255 });


	//  camera
	camera = createEntity();
	camera->addComponentByClass<CameraComponent>()->setAsActiveCamera();
	camera->getComponentByClass<CameraComponent>()->setYaw(-90.0f);
	camera->setPosition(Vector3{ -10.0f, CAMERA_HEIGHT, 0.0f });
	camera->setRotation(Quaternion::createLookAt(camera->getPosition(), CAMERA_TARGET, Vector3::unitY));


	//  directionnal light
	Entity* dir_light = createEntity();
	std::shared_ptr<DirectionalLightComponent> dir_light_comp = dir_light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color::white);
	dir_light_comp->setDirection(Vector3::negUnitY);
	dir_light_comp->setAmbientStrength(0.1f);
	dir_light_comp->setDiffuseStrength(0.4f);


	//  floor
	Entity* floor = createEntity();
	floor->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	floor->setScale(100.0f);
	floor->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("floor_wood"));
	std::shared_ptr<BoxAABBColComp> floor_col_comp = floor->addComponentByClass<BoxAABBColComp>();
	floor_col_comp->setBox(Box{ Vector3{0.0f, -0.1f, 0.0f}, Vector3{0.5f, 0.1f, 0.5f} });
	floor_col_comp->setCollisionChannel("solid");


	//  props (code for the demoreel)
	
	Entity* floor_lamp = createEntity();
	floor_lamp->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("floorlamp"));
	std::shared_ptr<PointLightComponent> floor_light = floor_lamp->addComponentByClass<PointLightComponent>();
	floor_light->setColor(Color{ 238, 205, 120, 255 });
	floor_light->setDiffuseStrength(3.0f);

	Entity* chest = createEntity();
	chest->setPosition(Vector3{ 4.0f, 0.0f, 4.0f });
	chest->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-135.0f) });
	chest->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenchest"));

	Entity* chair = createEntity();
	chair->setPosition(Vector3{ -5.0f, 0.0f, 1.0f });
	chair->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(13.0f) });
	chair->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenchair"));

	Entity* brick = createEntity();
	brick->setPosition(Vector3{ 0.0f, 3.0f, -5.0f });
	brick->setScale(1.3f);
	brick->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("orangebrick"));

	std::shared_ptr<BoxAABBColComp> brick_col = brick->addComponentByClass<BoxAABBColComp>();
	brick_col->setBox(Box{ Vector3::zero, Vector3{0.65f, 0.17f, 0.33f} });
	std::shared_ptr<RigidbodyComponent> brick_rigidbody = brick->addComponentByClass<RigidbodyComponent>();
	brick_rigidbody->associateCollision(brick_col);
	brick_rigidbody->setPhysicsActivated(true);


	//  props (correction code not for the demoreel)

	floor_lamp->setScale(0.02f);
	floor_light->setUseDiffColorToSpecColor(true);
	floor_light->setFalloff(1.0f, 0.07f, 0.017f);
	floor_light->setOffset(Vector3{ 0.0f, 100.0f, 0.0f });
	floor_light->setAmbientStrength(0.3f);

	chest->setScale(0.12f);
	chest->addPosition(Vector3{ 0.0f, 1.1f, 0.0f });

	chair->setScale(0.04f);

	brick->setScale(0.06f);
	brick_col->setCollisionChannel("brick");
	brick_col->useOwnerScaleForBoxCenter = false;
	brick_col->useOwnerScaleForBoxSize = false;
	brick_rigidbody->setTestChannels({ "solid" });
	brickEntity = brick;
}

void DemoreelSceneTwo::unloadScene()
{
}

void DemoreelSceneTwo::updateScene(float dt)
{
	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		cameraMoving = !cameraMoving;
		if (cameraMoving)
		{
			cameraTimer = 0.0f;
			camera->setPosition(Vector3{ -10.0f, CAMERA_HEIGHT, 0.0f });
			camera->setRotation(Quaternion::createLookAt(camera->getPosition(), CAMERA_TARGET, Vector3::unitY));
		}
	}

	if (cameraMoving)
	{
		cameraTimer += dt * 0.3f;
		camera->setPosition(Vector3{Maths::cos(cameraTimer) * -10.0f, CAMERA_HEIGHT, Maths::sin(cameraTimer) * -10.0f});
		camera->setRotation(Quaternion::createLookAt(camera->getPosition(), CAMERA_TARGET, Vector3::unitY));

		timer += dt;
		if (timer >= 15.5f && !brickActivated)
		{
			brickActivated = true;
			brickEntity->getComponentByClass<RigidbodyComponent>()->setUseGravity(true);
		}
	}
}
