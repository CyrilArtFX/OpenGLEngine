#include "doomlikeGame.h"
#include <Assets/defaultAssets.h>

DoomlikeGame::DoomlikeGame()
{
}

void DoomlikeGame::load(Renderer* renderer_)
{
	renderer = renderer_;

	DefaultAssets::LoadDefaultAssets();

	loadScene(&testScene);
}

void DoomlikeGame::unloadGame()
{
}

void DoomlikeGame::updateGame(float dt)
{
}
