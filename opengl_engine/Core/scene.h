#pragma once
#include <ECS/entityContainer.h>

class Scene : public EntityContainer
{
public:
	virtual ~Scene() {} 

	void load();
	void unload(bool exitGame);
	void update(float dt);

	void lateUpdate();

protected:
	//  Overridable functions for user-created scenes
	// -----------------------------------------------
	virtual void loadScene() = 0;
	virtual void unloadScene() = 0;
	virtual void updateScene(float dt) {}

private:
	bool firstFrame{ true };
};