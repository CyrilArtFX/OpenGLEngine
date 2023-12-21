#include "game.h"

#include <iostream>

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

void Game::loadScene(std::weak_ptr<Scene> scene)
{
	if (!renderer)
	{
		std::cout << "Game renderer not setup !\n";
		return;
	}

	unloadActiveScene();
	activeScene = scene.lock();
	activeScene->load(renderer);
}

void Game::unloadActiveScene()
{
	if (activeScene) activeScene->unload();
	renderer->setCamera(&gamedefaultsNocam);
}
