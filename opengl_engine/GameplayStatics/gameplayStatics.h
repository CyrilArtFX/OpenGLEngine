#pragma once
#include <Core/game.h>
#include <Core/scene.h>
#include <Maths/Vector2Int.h>

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

	/*
	* Get the size of the Window.
	*/
	static Vector2Int GetWindowSize();



private:
	static Game* currentGame;
	static Scene* currentScene;
	static Vector2Int windowSize;


	friend class Engine;
	friend class Game;

	static void SetCurrentGame(Game* game);
	static void SetCurrentScene(Scene* scene);
	static void SetWindowSize(const Vector2Int& size);
};

