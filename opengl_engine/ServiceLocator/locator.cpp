#include "locator.h"

Physics* Locator::physicsService;
NullPhysics Locator::nullPhysicsService;

Physics& Locator::getPhysics()
{
	return *physicsService;
}

Physics& Locator::providePhysics(Physics* physicsService_)
{
	if (physicsService_ == NULL)
	{
		initialize(); //  revert to null service
		return getPhysics();
	}
	else
	{
		physicsService = physicsService_;
		return getPhysics();
	}
}

void Locator::initialize()
{
	physicsService = &nullPhysicsService;
}
