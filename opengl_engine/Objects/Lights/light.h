#pragma once
#include <Rendering/shader.h>
#include <Utils/color.h>


enum OldLightType : uint8_t
{
	OldUndefinedLight = 0,
	OldDirectionalLight = 1,
	OldPointLight = 2,
	OldSpotLight = 3
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


	inline OldLightType getLightType() { return lightType; }
		 
	inline bool isLoaded() { return loaded; }

	inline void turnOff() { off = true; }
	inline void turnOn() { off = false; }


protected:
	bool loaded{ false };
	bool off{ false };

	Color lightColor{ Color::white };
	float ambientStrength{ 0.01f };
	float diffuseStrength{ 0.7f };

	OldLightType lightType{ OldUndefinedLight };
};