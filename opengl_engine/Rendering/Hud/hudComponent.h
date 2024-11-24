#pragma once
#include <Utils/color.h>
#include <Maths/Vector2.h>
#include <Maths/Matrix4.h>

class HudComponent
{
public:
	HudComponent();
	HudComponent(const HudComponent& other);
	~HudComponent();
	HudComponent& operator=(const HudComponent& other) = delete;

	void setEnabled(const bool enabled_);
	bool getEnabled() const;

	void setHudTransform(const Vector2& pivot_, const Vector2& screenPos_, const Vector2& scale_, const float rotAngle_);
	void setPivot(const Vector2& pivot_);
	void setScreenPos(const Vector2& screenPos_);
	void setScale(const Vector2& scale_);
	void setRotAngle(const float rotAngle_);
	void setTintColor(const Color& tintColor_);

	Vector2 getPivot() const;
	Vector2 getScreenPos() const;
	Vector2 getScale() const;
	float getRotAngle() const;
	Color getTintColor() const;

	/* Hud elements size is often affected by something else that scale (for exemple, texture size for sprites). This function must be overriden in every class that inherit hud. */
	virtual Vector2 getSize() const = 0;
	Matrix4 getHudTransform() const;

private:
	bool enabled{ true };

	Vector2 pivot{ Vector2::halfUnit };
	Vector2 screenPos{ Vector2::zero };
	Vector2 scale{ Vector2::one };
	float rotAngle{ 0.0f };
	Color tintColor{ Color::white };

	Matrix4 hudTransform{ Matrix4::identity };

	void computeMatrix();
};

