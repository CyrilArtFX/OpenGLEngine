#include "locator.h"
#include "nullPhysics.h"
#include "nullRenderer.h"
#include "nullAudio.h"
#include "nullLog.h"

Physics* Locator::physicsService;
Renderer* Locator::rendererService;
Audio* Locator::audioService;
Log* Locator::logService;
NullPhysics Locator::nullPhysicsService;
NullRenderer Locator::nullRendererService;
NullAudio Locator::nullAudioService;
NullLog Locator::nullLogService;


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

Audio& Locator::getAudio()
{
	return *audioService;
}

Audio& Locator::provideAudio(Audio* audioService_)
{
	if (audioService_ == NULL)
	{
		audioService = &nullAudioService;
		return getAudio();
	}
	else
	{
		audioService = audioService_;
		return getAudio();
	}
}

Log& Locator::getLog()
{
	return *logService;
}

Log& Locator::provideLog(Log* logService_)
{
	if (logService_ == NULL)
	{
		logService = &nullLogService;
		return getLog();
	}
	else
	{
		logService = logService_;
		return getLog();
	}
}

void Locator::initialize()
{
	physicsService = &nullPhysicsService;
	rendererService = &nullRendererService;
	audioService = &nullAudioService;
	logService = &nullLogService;
}
