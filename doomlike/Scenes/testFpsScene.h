#pragma once
#include <Core/scene.h>


class TestFpsScene : public Scene
{
protected:
	void loadScene() override;
	void unloadScene() override;
};