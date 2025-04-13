#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <string>


class ButtonComponent : public Component, public Observer
{
protected:
	void init() override;
	void exit() override;
	void update(float deltaTime) override;

private:
	std::shared_ptr<class ModelRendererComponent> buttonModel;
	std::shared_ptr<class BoxAABBColComp> triggerBox;
	std::shared_ptr<class TextRendererComponent> text;

	int frameOutsideCount{ 0 };
	bool used{ false };

	void onBodyIntersect(class RigidbodyComponent& other);

	const std::string textContent{ "Click to play sound." };
};

