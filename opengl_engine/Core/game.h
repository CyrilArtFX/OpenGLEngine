#pragma once
#include <Rendering/renderer.h>
#include "scene.h"

class Camera;

class Game
{
public:
	virtual ~Game() {}

	virtual void load(Renderer* renderer_) = 0;
	void unload();
	virtual void unloadGame() = 0;

	virtual void updateGame(float dt) = 0; //  updateGame come first during a frame
	void updateScene(float dt);

	Camera& getActiveCamera();

	bool hasActiveScene();

protected:
	void loadScene(Scene* scene);
	void unloadActiveScene();

	Renderer* renderer{ nullptr };
	Scene* activeScene{ nullptr };

private:
	Camera gamedefaultsNocam; //  camera to return if there is no active scene
};