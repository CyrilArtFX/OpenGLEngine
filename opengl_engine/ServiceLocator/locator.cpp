#include "locator.h"

Physics* Locator::physicsService;
NullPhysics Locator::nullPhysicsService;
Renderer* Locator::rendererService;
NullRenderer Locator::nullRendererService;

Physics& Locator::getPhysics()
{
	return *physicsService;
}

Physics& Locator::providePhysics(Physics* physicsService_)
{
	if (physicsService_ == NULL)
	{
		physicsService = &nullPhysicsService;
		return getPhysics();
	}
	else
	{
		physicsService = physicsService_;
		return getPhysics();
	}
}

Renderer& Locator::getRenderer()
{
	return *rendererService;
}

Renderer& Locator::provideRenderer(Renderer* rendererService_)
{
	if (rendererService_ == NULL)
	{
		rendererService = &nullRendererService;
		return getRenderer();
	}
	else
	{
		rendererService = rendererService_;
		return getRenderer();
	}
}

void Locator::initialize()
{
	physicsService = &nullPhysicsService;
	rendererService = &nullRendererService;
}
