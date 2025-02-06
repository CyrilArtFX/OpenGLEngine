#pragma once

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

protected:
	friend class Entity;

	virtual void registerComponent() = 0;
	virtual void unregisterComponent() = 0;

	/** Called after the component has been created, but before it is registered. */
	virtual void init() {};

private:
	Entity* owner{ nullptr };

	bool componentRegistered{ false };

	void setOwner(Entity* owner_);
};

