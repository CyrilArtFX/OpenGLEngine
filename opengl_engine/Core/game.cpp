#include "game.h"

#include <iostream>

void Game::load(Renderer* renderer_)
{
	renderer = renderer_;

	loadGameAssets();
	loadGame();
}

void Game::unload()
{
	unloadActiveScene();

	unloadGame();
}

void Game::updateScene(float dt)
{
	if (activeScene) activeScene->update(dt);
}

Camera& Game::getActiveCamera()
{
	if (activeScene) return activeScene->getCamera();
	return gamedefaultsNocam;
}

bool Game::hasActiveScene()
{
	if (activeScene) return true;
	return false;
}

void Game::loadScene(Scene* scene)
{
	if (!renderer)
	{
		std::cout << "Game doesn't have access to the renderer !\n";
		return;
	}

	unloadActiveScene();
	activeScene = scene;
	activeScene->load(renderer);
}

void Game::unloadActiveScene()
{
	if (activeScene) activeScene->unload();
	renderer->setCamera(&gamedefaultsNocam);
}
