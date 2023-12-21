#include "expositionGame.h"

ExpositionGame::ExpositionGame()
{
}

void ExpositionGame::load(Renderer* renderer_)
{
	renderer = renderer_;

	loadScene(&expositionScene);
}

void ExpositionGame::unloadGame()
{
}

void ExpositionGame::updateGame(float dt)
{
}