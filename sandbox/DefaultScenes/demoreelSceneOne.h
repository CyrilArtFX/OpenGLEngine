#pragma once
#include <Core/scene.h>

class DemoreelSceneOne : public Scene
{
protected:
	void loadScene() override;
	void unloadScene() override;
	void updateScene(float dt) override;

private:
	Entity* camera{ nullptr };
	bool cameraMoving{ false };
};

