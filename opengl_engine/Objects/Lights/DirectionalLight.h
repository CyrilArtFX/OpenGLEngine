#pragma once
#include "light.h"
#include <Maths/vector3.h>


class DirectionalLight : public Light
{
public:
	DirectionalLight();

	void load(Color lightColor_, Vector3 direction_, float ambientStrength_ = 0.1f, float diffuseStrength_ = 0.5f);
	
	void use(Shader& litShader, int lightIndex) override;

	
	inline void setDirection(Vector3 newDirection) { direction = newDirection; }
	inline Vector3 getDirection() { return direction; }

private:
	Vector3 direction{ Vector3::unitX };
};

