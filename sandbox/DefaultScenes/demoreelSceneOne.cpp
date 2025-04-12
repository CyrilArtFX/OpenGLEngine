#include "demoreelSceneOne.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>
#include <Inputs/Input.h>

#include <Rendering/cameraComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Rendering/Lights/directionalLightComponent.h>
#include <Rendering/Text/textRendererComponent.h>


void DemoreelSceneOne::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  camera
	camera = createEntity();
	camera->addComponentByClass<CameraComponent>()->setAsActiveCamera();
	camera->setPosition(Vector3{ 7.0f, 2.0f, 0.0f });


	//  directionnal light
	Entity* dir_light = createEntity();
	std::shared_ptr<DirectionalLightComponent> dir_light_comp = dir_light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color::white);
	dir_light_comp->setDirection(Vector3::normalize(Vector3{ 1.0f, -1.0f, 0.0f }));
	dir_light_comp->setAmbientStrength(0.1f);
	dir_light_comp->setDiffuseStrength(0.4f);


	//  floors
	Entity* floor_1 = createEntity();
	floor_1->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	floor_1->setScale(20.0f);
	floor_1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("floor_stone"));
	Entity* floor_2 = createEntity();
	floor_2->setPosition(Vector3{ 20.0f, 0.0f, 0.0f });
	floor_2->setScale(20.0f);
	floor_2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("floor_stone"));
	Entity* floor_3 = createEntity();
	floor_3->setPosition(Vector3{ 40.0f, 0.0f, 0.0f });
	floor_3->setScale(20.0f);
	floor_3->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("floor_stone"));
	Entity* floor_4 = createEntity();
	floor_4->setPosition(Vector3{ 60.0f, 0.0f, 0.0f });
	floor_4->setScale(20.0f);
	floor_4->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("floor_stone"));


	//  props
	Entity* wooden_barrel = createEntity();
	wooden_barrel->setPosition(Vector3{ 18.0f, 0.0f, -4.0f });
	wooden_barrel->setScale(0.03f);
	wooden_barrel->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-55.0f) });
	wooden_barrel->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenbarrel"));

	Entity* wooden_beehive = createEntity();
	wooden_beehive->setPosition(Vector3{ 18.0f, 0.0f, 4.0f });
	wooden_beehive->setScale(0.03f);
	wooden_beehive->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-115.0f) });
	wooden_beehive->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenbeehive"));

	Entity* cannon_trailer = createEntity();
	cannon_trailer->setPosition(Vector3{ 30.0f, 0.0f, -5.0f });
	cannon_trailer->setScale(0.025f);
	cannon_trailer->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(30.0f)});
	cannon_trailer->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("cannontrailer"));

	Entity* wooden_wheelbarrow = createEntity();
	wooden_wheelbarrow->setPosition(Vector3{ 30.0f, 0.0f, 5.0f });
	wooden_wheelbarrow->setScale(0.05f);
	wooden_wheelbarrow->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-115.0f) });
	wooden_wheelbarrow->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenwheelbarrow"));

	Entity* roman_statue = createEntity();
	roman_statue->setPosition(Vector3{ 35.0f, 0.0f, 0.0f });
	roman_statue->setScale(0.04f);
	roman_statue->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-90.0f) });
	roman_statue->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("romanstatue"));

	Entity* wooden_lamp_1 = createEntity();
	wooden_lamp_1->setPosition(Vector3{ 24.0f, 0.0f, -4.0f });
	wooden_lamp_1->setScale(0.02f);
	wooden_lamp_1->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(250.0f) });
	wooden_lamp_1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenlamp"));
	std::shared_ptr<PointLightComponent> wooden_light_1 = wooden_lamp_1->addComponentByClass<PointLightComponent>();
	wooden_light_1->setColor(Color{ 238, 205, 120, 255 });
	wooden_light_1->setAmbientStrength(0.3f);
	wooden_light_1->setDiffuseStrength(1.2f);
	wooden_light_1->setUseDiffColorToSpecColor(true);

	Entity* wooden_lamp_2 = createEntity();
	wooden_lamp_2->setPosition(Vector3{ 24.0f, 0.0f, 4.0f });
	wooden_lamp_2->setScale(0.02f);
	wooden_lamp_2->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-250.0f) });
	wooden_lamp_2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("woodenlamp"));
	std::shared_ptr<PointLightComponent> wooden_light_2 = wooden_lamp_2->addComponentByClass<PointLightComponent>();
	wooden_light_2->setColor(Color{ 238, 205, 120, 255 });
	wooden_light_2->setAmbientStrength(0.3f);
	wooden_light_2->setDiffuseStrength(1.2f);
	wooden_light_2->setUseDiffColorToSpecColor(true);

	Entity* text = createEntity();
	//text->addComponentByClass<TextRendererComponent>()->setTextDatas("Cy-Engine", AssetManager::GetFont("octosquares_128"), Vector2{ 0.5f, 0.0f }, Vector2{ 0.5f, 0.0f }, Vector2{ 0.0f, 100.0f }, Vector2{ 0.7f, 0.7f }, 0.0f, Color::white);
}

void DemoreelSceneOne::unloadScene()
{
}

void DemoreelSceneOne::updateScene(float dt)
{
	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		cameraMoving = !cameraMoving;
		if(cameraMoving) camera->setPosition(Vector3{ 7.0f, 2.0f, 0.0f });
	}

	if (cameraMoving)
	{
		camera->addPosition(Vector3{ 4.0f * dt, 0.0f, 0.0f });
	}
}
