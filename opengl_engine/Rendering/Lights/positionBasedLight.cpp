#include "positionBasedLight.h"
#include <ECS/entity.h>
#include <Maths/Matrix4.h>

void PositionBasedLight::initializePosition()
{
	getOwner()->onTransformUpdated.registerObserver(this, Bind_0(&PositionBasedLight::onEntityMoved));
	recomputePosition();
}

Vector3 PositionBasedLight::getPosition() const
{
	return position;
}


void PositionBasedLight::setFalloff(float newConstant, float newLinear, float newQuadratic)
{
	constant = newConstant;
	linear = newLinear;
	quadratic = newQuadratic;
}

void PositionBasedLight::setOffset(Vector3 newOffset)
{
	offset = newOffset;
	recomputePosition();
}

void PositionBasedLight::setConstant(float newConstant)
{
	constant = newConstant;
}

void PositionBasedLight::setLinear(float newLinear)
{
	linear = newLinear;
}

void PositionBasedLight::setQuadratic(float newQuadratic)
{
	quadratic = newQuadratic;
}

Vector3 PositionBasedLight::getOffset() const
{
	return offset;
}

float PositionBasedLight::getConstant() const
{
	return constant;
}

float PositionBasedLight::getLinear() const
{
	return linear;
}

float PositionBasedLight::getQuadratic() const
{
	return quadratic;
}


void PositionBasedLight::exit()
{
	getOwner()->onTransformUpdated.unregisterObserver(this);
}

void PositionBasedLight::onEntityMoved()
{
	recomputePosition();
}

void PositionBasedLight::recomputePosition()
{
	Matrix4 light_pos_matrix = Matrix4::createTranslation(offset) * getOwner()->getModelMatrix();
	position = light_pos_matrix.getTranslation();
}
