#include "game.h"
#include <ServiceLocator/locator.h>
#include <GameplayStatics/gameplayStatics.h>


void Game::load()
{
	loadGameAssets();
	loadGame();
}

void Game::unload()
{
	unloadActiveScene(false);

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
	unloadActiveScene(true);
	activeScene = scene;
	GameplayStatics::SetCurrentScene(activeScene);
	activeScene->load();
}

void Game::unloadActiveScene(bool loadNewScene)
{
	if (activeScene) activeScene->unload(!loadNewScene);
	if (!loadNewScene) Locator::getRenderer().SetCamera(&gamedefaultsNocam);

	if (!loadNewScene) GameplayStatics::SetCurrentScene(nullptr);
}
