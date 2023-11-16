#include "flatEmissiveMaterial.h"

FlatEmissiveMaterial::FlatEmissiveMaterial(std::weak_ptr<Shader> shaderUsed, Vector3 emissiveColor_)
	: emissiveColor(emissiveColor_), Material(shaderUsed, Unlit)
{}

void FlatEmissiveMaterial::use()
{
	shader->setVec3("emissive", emissiveColor);
}


void FlatEmissiveMaterial::setEmissiveColor(Vector3 emissiveColor_)
{
	emissiveColor = emissiveColor_;
}
