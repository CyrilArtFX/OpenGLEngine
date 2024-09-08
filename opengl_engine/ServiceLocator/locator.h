#pragma once
#include "physics.h"
#include "renderer.h"
#include "audio.h"
#include "nullPhysics.h"
#include "nullRenderer.h"
#include "nullAudio.h"

class Locator
{
public:
	static Physics& getPhysics();
	static Physics& providePhysics(Physics* physicsService_);

	static Renderer& getRenderer();
	static Renderer& provideRenderer(Renderer* rendererService_);

	static Audio& getAudio();
	static Audio& provideAudio(Audio* audioService_);

private:
	static Physics* physicsService;
	static NullPhysics nullPhysicsService;

	static Renderer* rendererService;
	static NullRenderer nullRendererService;

	static Audio* audioService;
	static NullAudio nullAudioService;

	friend class Engine;
	static void initialize();
};

