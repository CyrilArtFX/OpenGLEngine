#pragma once
#include <Rendering/renderer.h>
#include "scene.h"

class Camera;

class Game
{
public:
	virtual ~Game() {}

	void load(Renderer* renderer_);
	void unload();

	virtual void updateGame(float dt) = 0; //  updateGame come before updateScene during a frame
	void updateScene(float dt);

	virtual Camera& getActiveCamera();

	bool hasActiveScene();

protected:
	virtual void loadGameAssets() = 0;
	virtual void loadGame() = 0;

	virtual void unloadGame() = 0;

	void loadScene(Scene* scene);
	void unloadActiveScene(bool loadNewScene);

	Renderer* renderer{ nullptr };
	Scene* activeScene{ nullptr };

private:
	Camera gamedefaultsNocam; //  camera to return if there is no active scene
};