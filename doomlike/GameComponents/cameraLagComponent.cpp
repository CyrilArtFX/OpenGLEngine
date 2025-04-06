#include "cameraLagComponent.h"
#include <ECS/entity.h>
#include <Maths/Maths.h>


void CameraLagComponent::setupLag(const float& lagSpeed_, const float& lagMaxDist_)
{
	lagSpeed = lagSpeed_;
	lagMaxDist = lagMaxDist_;
}

void CameraLagComponent::teleport()
{
	lagEntityPos = getOwner()->getPosition();
}

void CameraLagComponent::setLagSpeed(const float& lagSpeed_)
{
	lagSpeed = lagSpeed_;
}

void CameraLagComponent::getLagMaxDist(const float& lagMaxDist_)
{
	lagMaxDist = lagMaxDist_;
}

void CameraLagComponent::init()
{
	//  reset the values in case this component was used before (the component manager is a memory pool)
	active = false;
	posOffset = Vector3::zero;
	rotOffset = Quaternion::identity;
	yawOffset = 0.0f;
	pitchOffset = 0.0f;
	rollOffset = 0.0f;
	fov = 45.0f;
	computedPos = Vector3::zero;
	computedForward = Vector3::unitX;
	computedUp = Vector3::unitY;
	computedRight = Vector3::unitZ;
	lagSpeed = 0.0f;
	lagMaxDist = 0.0f;


	lagEntityPos = getOwner()->getPosition();
}

void CameraLagComponent::update(float deltaTime)
{
	const Vector3 target_entity_pos = getOwner()->getPosition();
	float lag_dist = Vector3::Distance(lagEntityPos, target_entity_pos);

	if (lag_dist > lagMaxDist)
	{
		const Vector3 inv_lag_dir = Vector3::normalize(target_entity_pos - lagEntityPos);
		lagEntityPos = target_entity_pos - inv_lag_dir * lagMaxDist;
		lag_dist = lagMaxDist;
	}

	float lag_alpha = Maths::min(lagSpeed * deltaTime / lag_dist, 1.0f);
	lagEntityPos = Vector3::lerp(lagEntityPos, target_entity_pos, lag_alpha);
}

void CameraLagComponent::computeCameraVectors(bool computePos, bool computeDirections)
{
	Entity* owner = getOwner();

	if (computePos)
	{
		Matrix4 lag_pos_matrix =
			Matrix4::createScale(owner->getScale()) *
			Matrix4::createFromQuaternion(owner->getRotation()) *
			Matrix4::createTranslation(lagEntityPos);
		Matrix4 cam_pos_matrix = Matrix4::createTranslation(posOffset) * lag_pos_matrix;
		computedPos = cam_pos_matrix.getTranslation();
	}

	if (computeDirections)
	{
		Quaternion cam_rot = Quaternion::concatenate(rotOffset, owner->getRotation());
		computedForward = Vector3::transform(Vector3::unitX, cam_rot);
		computedUp = Vector3::transform(Vector3::unitY, cam_rot);
		computedRight = Vector3::transform(Vector3::unitZ, cam_rot);
	}
}
