#include "lightComponent.h"
#include <ServiceLocator/locator.h>


LightType LightComponent::getLightType()
{
	return lightType;
}

void LightComponent::setActive(bool activeValue)
{
	active = activeValue;
}

bool LightComponent::isActive()
{
	return active;
}


void LightComponent::setColor(Color newColor)
{
	lightColor = newColor;
}

void LightComponent::setAmbientStrength(float newAmbientStrength)
{
	ambientStrength = newAmbientStrength;
}

void LightComponent::setDiffuseStrength(float newDiffuseStrength)
{
	diffuseStrength = newDiffuseStrength;
}

Color LightComponent::getColor()
{
	return lightColor;
}

float LightComponent::getAmbientStrength()
{
	return ambientStrength;
}

float LightComponent::getDiffuseStrength()
{
	return diffuseStrength;
}



void LightComponent::registerComponent()
{
	//  we can't register the light component to the renderer here, cause we need to wait for the user to initialize the light
}

void LightComponent::unregisterComponent()
{
	onLightUnregistered();
	Locator::getRenderer().RemoveLight(this);
}
