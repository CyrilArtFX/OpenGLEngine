#include "demoreelSceneAudio.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>

#include <GameComponents/buttonComponent.h>
#include <Rendering/Lights/directionalLightComponent.h>
#include <PrefabFactories/floorCeilingFactory.h>


void DemoreelSceneAudio::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 0, 5, 20, 255 });


	//  prefabs
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 20.0f, 20.0f }, true);

	//  entities
	Entity* button = createEntity();
	Entity* light = createEntity();

	button->setPosition(Vector3{ 3.0f, 0.0f, 0.0f });

	//  components
	button->addComponentByClass<ButtonComponent>();

	std::shared_ptr<DirectionalLightComponent> dir_light_comp = light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color::white);
	dir_light_comp->setDirection(Vector3::normalize(Vector3{ 1.0f, -1.0f, 0.0f }));
	dir_light_comp->setAmbientStrength(0.1f);
	dir_light_comp->setDiffuseStrength(0.7f);


	//  player spawn point
	spawnPoint = createEntity();
	spawnPoint->setPosition(Vector3{ -5.0f, 0.0f, 0.0f });
}

void DemoreelSceneAudio::unloadScene()
{
}
