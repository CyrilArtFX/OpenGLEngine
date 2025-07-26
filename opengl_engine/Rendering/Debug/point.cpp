#include "point.h"
#include <Assets/assetManager.h>

Point::Point()
{
	cubeMesh = &AssetManager::GetSingleMesh("debug_cube");

	setScale(pointSize);
}

void Point::setPointPostition(Vector3 pointPosition)
{
	setPosition(pointPosition);
}

void Point::draw(Material& debugMaterial, const Color& drawColor)
{
	debugMaterial.getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());
	debugMaterial.getShader().setVec3("color", drawColor);

	cubeMesh->draw(false);
}
