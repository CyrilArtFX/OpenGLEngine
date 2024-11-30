#include "hudComponent.h"

HudComponent::HudComponent()
{
	// TODO: bind to the onScreenResize event when it will be created
}

HudComponent::HudComponent(const HudComponent& other) :
	pivot(other.pivot), screenPos(other.screenPos), scale(other.scale), rotAngle(other.rotAngle), hudTransform(other.hudTransform)
{
	// TODO: bind to the onScreenResize event when it will be created
}

HudComponent::~HudComponent()
{
	// TODO: unbind from the onScreenResize event when it will be created
}



void HudComponent::setEnabled(const bool enabled_)
{
	enabled = enabled_;
}

bool HudComponent::getEnabled() const
{
	return enabled;
}


void HudComponent::setHudTransform(const Vector2& pivot_, const Vector2& screenPos_, const Vector2& scale_, const float rotAngle_)
{
	screenPos = screenPos_;
	scale = scale_;
	rotAngle = rotAngle_;
	setPivot(pivot_); //  setPivot function will recompute the transform matrix
}

void HudComponent::setPivot(const Vector2& pivot_)
{
	pivot = Vector2{ Maths::clamp<float>(pivot_.x, 0.0f, 1.0f), Maths::clamp<float>(pivot_.y, 0.0f, 1.0f) };

	computeMatrix();
}

void HudComponent::setScreenPos(const Vector2& screenPos_)
{
	screenPos = screenPos_;

	computeMatrix();
}

void HudComponent::setScale(const Vector2& scale_)
{
	scale = scale_;

	computeMatrix();
}

void HudComponent::setRotAngle(const float rotAngle_)
{
	rotAngle = rotAngle_;

	computeMatrix();
}

void HudComponent::setTintColor(const Color& tintColor_)
{
	tintColor = tintColor_;
}


Vector2 HudComponent::getPivot() const
{
	return pivot;
}

Vector2 HudComponent::getScreenPos() const
{
	return screenPos;
}

Vector2 HudComponent::getScale() const
{
	return scale;
}

float HudComponent::getRotAngle() const
{
	return rotAngle;
}

Color HudComponent::getTintColor() const
{
	return tintColor;
}

Matrix4 HudComponent::getHudTransform() const
{
	return hudTransform;
}




void HudComponent::computeMatrix()
{
	if (!needToComputeMatrix()) return;

	const Vector2 size = getSize();
	const Vector2 pivot_inv_y = Vector2{ pivot.x, 1.0f - pivot.y };

	hudTransform =
		Matrix4::createScale(Vector3{ size, 1.0f }) * //  scale to the size of the hud element
		Matrix4::createTranslation(size * -pivot_inv_y) * //  translate to use the pivot
		Matrix4::createRotationZ(Maths::toRadians(rotAngle)) * //  rotate the hud element
		Matrix4::createTranslation(screenPos); //  translate to the position of the hud element
}