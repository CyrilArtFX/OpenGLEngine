#pragma once
#include <Rendering/material.h>
#include <Utils/Color.h>

class DebugRenderBase
{
public:
	void setupDebugDraw(const Color& color, const float duration);
	bool updateLifetime(float dt);
	Color getColor();

	virtual void draw(Material& material, const Color& color) = 0;

protected:
	Color debugColor{ Color::white };
	float lifetime{ 0.0f };
};