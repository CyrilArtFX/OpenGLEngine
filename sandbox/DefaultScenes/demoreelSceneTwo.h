#pragma once
#include <Core/scene.h>

class DemoreelSceneTwo : public Scene
{
protected:
	void loadScene() override;
	void unloadScene() override;
	void updateScene(float dt) override;

private:
	Entity* camera{ nullptr };
	bool cameraMoving{ false };
	float cameraTimer{ 0.0f };

	Entity* brickEntity{ nullptr };
	float timer{ 0.0f };
	bool brickActivated{ false };
};

