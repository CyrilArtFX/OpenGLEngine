#pragma once
#include <Core/scene.h>


class DoomlikeLevelDebug : public Scene
{
public:
	void updateScene(float dt) override;

protected:
	void loadScene() override;
	void unloadScene() override;
};

