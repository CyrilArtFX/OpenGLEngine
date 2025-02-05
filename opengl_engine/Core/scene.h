#pragma once
#include <ECS/entityContainer.h>
#include <Rendering/camera.h>

class Scene : public EntityContainer
{
public:
	virtual ~Scene() {} 

	void load();
	void unload(bool exitGame);
	void update(float dt);
	
	/** Get the camera of the scene. User is responsible of providing a valid camera to the scene (subject to change). */
	Camera& getCamera();

	void lateUpdate();

protected:
	//  Overridable functions for user-created scenes
	// -----------------------------------------------
	virtual void loadScene() = 0;
	virtual void unloadScene() = 0;
	virtual void updateScene(float dt) = 0;

	Camera* currentCam{ nullptr };

private:
	bool firstFrame{ true };
};