#pragma once
#include <Core/game.h>
#include <Core/scene.h>

class Engine;

class GameplayStatics
{
public:
	/*
	* Get the currently active Game.
	*/
	static Game* GetGame();

	/*
	* Get the currently active Scene.
	*/
	static Scene* GetActiveScene();



private:
	static Game* currentGame;
	static Scene* currentScene;


	friend class Engine;
	friend class Game;

	static void SetCurrentGame(Game* game);
	static void SetCurrentScene(Scene* scene);
};

