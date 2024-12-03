#pragma once
#include <Utils/color.h>
#include <Maths/Vector2.h>
#include <Maths/Matrix4.h>
#include <Events/observer.h>

class HudComponent : public Observer
{
public:
	HudComponent();
	HudComponent(const HudComponent& other);
	~HudComponent();
	HudComponent& operator=(const HudComponent& other) = delete;

	void setEnabled(const bool enabled_);
	bool getEnabled() const;

	void setHudTransform(const Vector2& screenAnchor_, const Vector2& pivot_, const Vector2& pos_, const Vector2& scale_, const float rotAngle_);
	void setScreenAnchor(const Vector2& screenAnchor_);
	void setPivot(const Vector2& pivot_);
	void setPos(const Vector2& pos_);
	void setScale(const Vector2& scale_);
	void setRotAngle(const float rotAngle_);
	void setTintColor(const Color& tintColor_);

	Vector2 getPivot() const;
	Vector2 getPos() const;
	Vector2 getScale() const;
	float getRotAngle() const;
	Color getTintColor() const;

	/* Hud elements size is often affected by something else that scale (for exemple, texture size for sprites). This function must be overriden in every class that inherit hud. */
	virtual Vector2 getSize() const = 0;
	Vector2 getScreenPos() const;
	Matrix4 getHudTransform() const;

protected:
	/* Does the hud component need to compute the transformation matrix? (For exemple, texts doesn't need to.) This function must be overriden in every class that inherit hud. */
	virtual bool needToComputeMatrix() const = 0;

private:
	bool enabled{ true };

	Vector2 screenAnchor{ Vector2::halfUnit };
	Vector2 pivot{ Vector2::halfUnit };
	Vector2 pos{ Vector2::zero };
	Vector2 scale{ Vector2::one };
	float rotAngle{ 0.0f };
	Color tintColor{ Color::white };

	Vector2 screenPos{ Vector2::zero };
	Matrix4 hudTransform{ Matrix4::identity };

	void updatePosWithAnchor();
	void computeMatrix();
};

