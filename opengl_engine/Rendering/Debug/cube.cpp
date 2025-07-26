#include "cube.h"
#include <Assets/assetManager.h>

Cube::Cube()
{
	cubeMesh = &AssetManager::GetSingleMesh("debug_cube");
}

void Cube::setBox(const Box& boxInfos)
{
	box = boxInfos;

	computeBoxModelMatrix();
}

void Cube::draw(Material& debugMaterial, const Color& drawColor)
{
	debugMaterial.getShader().setMatrix4("model", boxModelMatrix.getAsFloatPtr());
	debugMaterial.getShader().setVec3("color", drawColor);

	cubeMesh->draw(true);
}

void Cube::computeBoxModelMatrix()
{
	boxModelMatrix =
		Matrix4::createScale(box.getHalfExtents() * 2.0f) *
		Matrix4::createTranslation(box.getCenterPoint());
}
