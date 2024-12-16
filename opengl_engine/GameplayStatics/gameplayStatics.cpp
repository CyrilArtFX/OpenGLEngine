#include "gameplayStatics.h"
#include <ServiceLocator/locator.h>

Game* GameplayStatics::currentGame = nullptr;
Scene* GameplayStatics::currentScene = nullptr;
Vector2Int GameplayStatics::windowSize = Vector2Int::zero;
Event<const Vector2Int> GameplayStatics::OnScrenResize;

Game* GameplayStatics::GetGame()
{
	if (!currentGame)
	{
		Locator::getLog().LogMessage_Category("Gameplay Statics: There is no currently referenced Game.", LogCategory::Error);
		return nullptr;
	}

	return currentGame;
}

Scene* GameplayStatics::GetActiveScene()
{
	if (!currentScene)
	{
		Locator::getLog().LogMessage_Category("Gameplay Statics: There is no active Scene.", LogCategory::Error);
		return nullptr;
	}

	return currentScene;
}

Vector2Int GameplayStatics::GetWindowSize()
{
	return windowSize;
}


void GameplayStatics::SetCurrentGame(Game* game)
{
	currentGame = game;
}

void GameplayStatics::SetCurrentScene(Scene* scene)
{
	currentScene = scene;
}

void GameplayStatics::SetWindowSize(const Vector2Int& size)
{
	windowSize = size;
}
