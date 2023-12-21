#include "expositionGame.h"
#include <Assets/defaultAssets.h>

ExpositionGame::ExpositionGame()
{
}

void ExpositionGame::load(Renderer* renderer_)
{
	renderer = renderer_;

	DefaultAssets::LoadDefaultAssets();

	loadScene(&expositionScene);
}

void ExpositionGame::unloadGame()
{
}

void ExpositionGame::updateGame(float dt)
{
}