#pragma once
#include "light.h"
#include <Maths/vector3.h>


class PointLight : public Light
{
public:
	PointLight();

	void load(Color lightColor_, Vector3 position_, float ambientStrength_ = 0.01f, float diffuseStrength_ = 0.7f,
		float constant_ = 1.0f, float linear_ = 0.09f, float quadratic_ = 0.032f);

	void use(Shader& litShader, int lightIndex) override;


	inline void setPosition(Vector3 newPosition) { position = newPosition; }
	inline Vector3 getPosition() { return position; }

	inline void setConstant(float newConstant) { constant = newConstant; }
	inline float getConstant() { return constant; }

	inline void setLinear(float newLinear) { linear = newLinear; }
	inline float getLinear() { return linear; }

	inline void setQuadratic(float newQuadratic) { quadratic = newQuadratic; }
	inline float getQuadratic() { return quadratic; }

private:
	Vector3 position{ Vector3::zero };

	float constant{ 0.0f };
	float linear{ 0.0f };
	float quadratic{ 0.0f };
};

