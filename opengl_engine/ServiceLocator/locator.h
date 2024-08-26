#pragma once
#include "physics.h"
#include "renderer.h"
#include "nullPhysics.h"
#include "nullRenderer.h"

class Locator
{
public:
	static Physics& getPhysics();
	static Physics& providePhysics(Physics* physicsService_);

	static Renderer& getRenderer();
	static Renderer& provideRenderer(Renderer* rendererService_);

private:
	static Physics* physicsService;
	static NullPhysics nullPhysicsService;

	static Renderer* rendererService;
	static NullRenderer nullRendererService;

	friend class Engine;
	static void initialize();
};

