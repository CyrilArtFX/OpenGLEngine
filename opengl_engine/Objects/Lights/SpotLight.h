#pragma once
#include "light.h"
#include <Maths/Vector3.h>
#include <Maths/Maths.h>


class SpotLight : public Light
{
public:
	SpotLight(LightType lightType_, Color lightColor_, Vector3 position_, Vector3 direction_, float ambientStrength_ = 0.01f, float diffuseStrength_ = 0.7f,
		float cutOff_ = Maths::cos(Maths::toRadians(12.5f)), float outerCutOff_ = Maths::cos(Maths::toRadians(17.5f)), 
		float constant_ = 1.0f, float linear_ = 0.09f, float quadratic_ = 0.032f);
	SpotLight() = delete;

	void use(Shader& litShader, int lightIndex) override;


	inline void setPosition(Vector3 newPosition) { position = newPosition; }
	inline Vector3 getPosition() { return position; }

	inline void setDirection(Vector3 newDirection) { direction = newDirection; }
	inline Vector3 getDirection() { return direction; }

	inline void setCutOff(float newCutOff) { cutOff = newCutOff; }
	inline float getCutOff() { return cutOff; }

	inline void setOuterCutOff(float newOuterCutOff) { outerCutOff = newOuterCutOff; }
	inline float getOuterCutOff() { return outerCutOff; }

	inline void setConstant(float newConstant) { constant = newConstant; }
	inline float getConstant() { return constant; }

	inline void setLinear(float newLinear) { linear = newLinear; }
	inline float getLinear() { return linear; }

	inline void setQuadratic(float newQuadratic) { quadratic = newQuadratic; }
	inline float getQuadratic() { return quadratic; }

private:
	Vector3 position;
	Vector3 direction;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
};
