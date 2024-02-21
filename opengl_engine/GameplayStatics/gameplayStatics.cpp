#include "gameplayStatics.h"
#include <iostream>

Game* GameplayStatics::currentGame = nullptr;
Scene* GameplayStatics::currentScene = nullptr;

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


void GameplayStatics::SetCurrentGame(Game* game)
{
	currentGame = game;
}

void GameplayStatics::SetCurrentScene(Scene* scene)
{
	currentScene = scene;
}