#pragma once
#include <Rendering/shader.h>
#include <Utils/Color.h>


enum LightType
{
	Directionnal,
	Point,
	Spot
};


class Light
{
public:
	Light(LightType lightType_): lightType(lightType_) {}
	virtual ~Light() {}

	virtual void use(Shader& litShader) = 0;


	inline void setColor(Color newColor) { lightColor = newColor; }
	inline Color getColor() { return lightColor; }

	inline void setAmbientStrength(float newAmbientStrength) { ambientStrength = newAmbientStrength; }
	inline float getAmbientStrength() { return ambientStrength; }

	inline void setDiffuseStrength(float newDiffuseStrength) { diffuseStrength = newDiffuseStrength; }
	inline float getDiffuseStrength() { return diffuseStrength; }


	inline LightType getLightType() { return lightType; }
		 
protected:
	Color lightColor{ Color::white };
	float ambientStrength{ 0.01f };
	float diffuseStrength{ 0.7f };

private:
	LightType lightType;
};