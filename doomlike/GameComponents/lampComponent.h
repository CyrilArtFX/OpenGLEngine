#pragma once
#include <ECS/component.h>

class PointLightComponent;
class ModelRendererComponent;


class LampComponent : public Component
{
public:
	void setup(std::weak_ptr<PointLightComponent> lightComp, std::weak_ptr<ModelRendererComponent> modelRendererComp, bool setupChandelier);
	void changeStatus(bool lightOn);

protected:
	void update(float deltaTime) override;
	void init() override;
	void exit() override;

private:
	std::shared_ptr<PointLightComponent> light;
	std::shared_ptr<ModelRendererComponent> modelRenderer;

	bool isChandelier{ false };
	bool compValid{ false };

	float timer{ 0.0f };
	bool reverse{ false };
	float baseLightIntensity{ 0.0f };
};

