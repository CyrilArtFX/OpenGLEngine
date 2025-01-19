#pragma once
#include <iostream>
class Entity;

class Component
{
public:
	Component() = delete;
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	Component(Entity* owner_);
	~Component();

	Entity* getOwner() const;

	/** Called after the component has been created. */
	virtual void init() {};

protected:
	friend class Entity;

	virtual void registerComponent() = 0;
	virtual void unregisterComponent() = 0;

private:
	Entity* owner;

	bool componentRegistered;
};

