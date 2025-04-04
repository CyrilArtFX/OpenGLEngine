#include "lampComponent.h"
#include <ECS/entity.h>
#include <Assets/assetManager.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Rendering/modelRendererComponent.h>

#include <stdlib.h>
#include <time.h>


void LampComponent::setup(std::weak_ptr<PointLightComponent> lightComp, std::weak_ptr<ModelRendererComponent> modelRendererComp, bool setupChandelier)
{
	light = lightComp.lock();
	modelRenderer = modelRendererComp.lock();

	isChandelier = setupChandelier;
	baseLightIntensity = isChandelier ? 0.4f : 0.22f;

	srand(static_cast<unsigned int>(time(NULL)));
	timer = float(rand() % 100) / 100.0f;

	light->setDiffuseStrength(baseLightIntensity + (Maths::sin(timer) / 11.0f));

	compValid = light && modelRenderer; //  prevent wrongly initialized lamp component to crash the game
}

void LampComponent::changeStatus(bool lightOn)
{
	if (!compValid) return;

	light->setActive(lightOn);
	
	if (isChandelier)
	{
		modelRenderer->getModel().changeMaterial(2, AssetManager::GetMaterial(lightOn ? "flame" : "chandelier_candle"));
		modelRenderer->getModel().changeMaterial(3, AssetManager::GetMaterial(lightOn ? "flame" : "flame_off"));
	}
	else
	{
		modelRenderer->getModel().changeMaterial(1, AssetManager::GetMaterial(lightOn ? "flame" : "flame_off"));
	}
}

void LampComponent::update(float deltaTime)
{
	if (!compValid) return;

	if (reverse)
	{
		timer -= deltaTime;
		if (timer < 0.0f) reverse = false;
	}
	else
	{
		timer += deltaTime;
		if (timer > 0.0f) reverse = true;
	}

	light->setDiffuseStrength(baseLightIntensity + (Maths::sin(timer) / 11.0f));
}