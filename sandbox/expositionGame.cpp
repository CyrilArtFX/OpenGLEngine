#include "expositionGame.h"
#include <DefaultScenes/expositionScene.h>

ExpositionGame::ExpositionGame()
{
}

void ExpositionGame::load(Renderer* renderer_)
{
	renderer = renderer_;

	loadScene(std::make_shared<ExpositionScene>());
}

void ExpositionGame::unloadGame()
{
}

void ExpositionGame::updateGame(float dt)
{
}