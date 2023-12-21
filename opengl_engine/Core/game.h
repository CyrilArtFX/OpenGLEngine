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
	void loadScene(std::weak_ptr<Scene> scene);
	void unloadActiveScene();

	Renderer* renderer;
	std::shared_ptr<Scene> activeScene;

private:
	Camera gamedefaultsNocam; //  camera to return if there is no active scene
};