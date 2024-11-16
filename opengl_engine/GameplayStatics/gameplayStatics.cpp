#include "gameplayStatics.h"
#include <iostream>

Game* GameplayStatics::currentGame = nullptr;
Scene* GameplayStatics::currentScene = nullptr;
Vector2Int GameplayStatics::windowSize = Vector2Int::zero;

Game* GameplayStatics::GetGame()
{
	if (!currentGame)
	{
		std::cout << "GameplayStatics Error: No game is referenced.\n";
		return nullptr;
	}

	return currentGame;
}

Scene* GameplayStatics::GetActiveScene()
{
	if (!currentScene)
	{
		std::cout << "GameplayStatics Error: There is no active scene.\n";
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
