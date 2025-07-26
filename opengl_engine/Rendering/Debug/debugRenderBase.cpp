#include "debugRenderBase.h"

void DebugRenderBase::setupDebugDraw(const Color& color, const float duration)
{
	debugColor = color;
	lifetime = duration;
}

bool DebugRenderBase::updateLifetime(float dt)
{
	lifetime -= dt;
	return lifetime < 0.0f;
}

Color DebugRenderBase::getColor()
{
	return debugColor;
}
