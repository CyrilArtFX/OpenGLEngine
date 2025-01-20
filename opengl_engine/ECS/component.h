#pragma once
#include <iostream>
class Entity;

class Component
{
public:
	Component();
	~Component();

	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	/** Get the Entity that owns this component. */
	Entity* getOwner() const;

	/** Called after the component has been created. */
	virtual void init() {};

protected:
	friend class Entity;

	virtual void registerComponent() = 0;
	virtual void unregisterComponent() = 0;

private:
	Entity* owner{ nullptr };

	bool componentRegistered{ false };

	void setOwner(Entity* owner_);
};

