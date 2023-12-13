#pragma once
#include <Rendering/shader.h>
#include <Utils/color.h>


enum LightType
{
	Undefined,
	Directionnal,
	Point,
	Spot
};


class Light
{
public:
	Light() {}
	virtual ~Light() {}

	virtual void use(Shader& litShader, int lightIndex) = 0;


	inline void setColor(Color newColor) { lightColor = newColor; }
	inline Color getColor() { return lightColor; }

	inline void setAmbientStrength(float newAmbientStrength) { ambientStrength = newAmbientStrength; }
	inline float getAmbientStrength() { return ambientStrength; }

	inline void setDiffuseStrength(float newDiffuseStrength) { diffuseStrength = newDiffuseStrength; }
	inline float getDiffuseStrength() { return diffuseStrength; }


	inline LightType getLightType() { return lightType; }
		 
	inline bool isLoaded() { return loaded; }


protected:
	bool loaded{ false };

	Color lightColor{ Color::white };
	float ambientStrength{ 0.01f };
	float diffuseStrength{ 0.7f };

	LightType lightType{ Undefined };
};