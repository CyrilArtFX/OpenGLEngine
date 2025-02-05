#include "game.h"
#include "scene.h"
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

	clearEntities();
}

void Game::update(float dt)
{
	updateGame(dt);

	if (activeScene) activeScene->update(dt);
}

Camera& Game::getActiveCamera()
{
	if (activeScene) return activeScene->getCamera();

	Locator::getLog().LogMessage_Category("Game: Tried to get the active camera but there is no active scene.", LogCategory::Error);
	return gamedefaultsNocam;
}

bool Game::hasActiveScene()
{
	if (activeScene) return true;
	return false;
}

void Game::lateUpdate()
{
	updateEntities();
	if (activeScene) activeScene->lateUpdate();
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
