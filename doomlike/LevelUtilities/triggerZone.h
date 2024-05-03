#pragma once
#include <Objects/Object.h>

#include <Events/event.h>
#include <Events/observer.h>

class TriggerZone : public Object, public Observer
{
public:
	TriggerZone() {}

	void setup(Vector3 position, Vector3 size);
	void disableZone();

	Event<> onPlayerEnter;

private:
	void onBodyIntersect(class RigidbodyComponent& other);
	RigidbodyComponent* rigidbody;
};

