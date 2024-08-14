#pragma once
#include "physics.h"
#include "nullPhysics.h"

class Locator
{
public:
	static Physics& getPhysics();

	static Physics& providePhysics(Physics* physicsService_);


private:
	static Physics* physicsService;
	static NullPhysics nullPhysicsService;

	friend class Engine;
	static void initialize();
};

