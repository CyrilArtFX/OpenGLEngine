#pragma once
#include "physics.h"
#include "renderer.h"
#include "audio.h"
#include "log.h"

class NullPhysics;
class NullRenderer;
class NullAudio;
class NullLog;

class Locator
{
public:
	static Physics& getPhysics();
	static Physics& providePhysics(Physics* physicsService_);

	static Renderer& getRenderer();
	static Renderer& provideRenderer(Renderer* rendererService_);

	static Audio& getAudio();
	static Audio& provideAudio(Audio* audioService_);

	static Log& getLog();
	static Log& provideLog(Log* logService_);

private:
	static Physics* physicsService;
	static NullPhysics nullPhysicsService;

	static Renderer* rendererService;
	static NullRenderer nullRendererService;

	static Audio* audioService;
	static NullAudio nullAudioService;

	static Log* logService;
	static NullLog nullLogService;

	friend class Engine;
	static void initialize();
};

