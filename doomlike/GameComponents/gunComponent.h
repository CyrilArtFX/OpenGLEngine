#pragma once
#include <ECS/component.h>
#include <Events/observer.h>


/**
* This component is responsible of the shoot.
* It automatically create the needed components on its entity.
*/
class GunComponent : public Component, public Observer
{
public:
	void reset();

protected:
	void init() override;
	void exit() override;
	void update(float deltaTime) override;
	void onPlayerTransformUpdated();

private:
	Entity* entity{ nullptr };
	std::shared_ptr<class PlayerComponent> player;
	std::shared_ptr<class ModelRendererComponent> gunModel;
	std::shared_ptr<class TextRendererComponent> ammoText;
	std::shared_ptr<class SpriteRendererComponent> crosshairSprite;

	bool gunValid{ false };
	int ammoCount{ 0 };
	float reloadTimer{ 0.0f };

	void writeAmmoText();

	const int ammoMax{ 5 };
	const float reloadDuration{ 0.5f };
	const float shootVelocity{ 15.0f };
	const float bulletLifetime{ 3.0f };
};

