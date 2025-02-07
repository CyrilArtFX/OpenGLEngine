#pragma once
#include <ECS/entityContainer.h>

class Scene;

class Game : public EntityContainer
{
public:
	virtual ~Game() {}

	void load();
	void unload();
	void update(float dt);

	bool hasActiveScene();

	void lateUpdate();

protected:
	//  Overridable functions for user-created games
	// ----------------------------------------------
	virtual void loadGameAssets() = 0;
	virtual void loadGame() = 0;
	virtual void unloadGame() = 0;
	virtual void updateGame(float dt) = 0;

	/**
	* Load a scene to the game. It will unload the previous active scene.
	* Can be used to reload the current scene.
	* @param	scene	The scene to load.
	*/
	void loadScene(Scene* scene);

	/**
	* Unload the current active scene.
	* This function is automatically called when loading a new scene or when exiting the game, so you shouldn't have to call it manually.
	* @param	loadNewScene	False if there is no new scene to be loaded after the unload (eg. exiting the game).
	*/
	void unloadActiveScene(bool loadNewScene);

	Scene* activeScene{ nullptr };
};