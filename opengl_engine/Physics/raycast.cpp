#include "raycast.h"

RaycastHitInfos RaycastHitInfos::defaultInfos(Vector3::zero, Vector3::zero, std::numeric_limits<float>::max(), nullptr);



Raycast::Raycast(const Vector3& startPoint, const Vector3& endPoint, float drawDebugTime, bool loadPersistent) :
	PhysicEntity(loadPersistent),
	drawDebugLineOne(), drawDebugLineTwo(), drawDebugPointHit(), drawDebugTimer(drawDebugTime)
{
	drawDebugLineOne.setPoints(startPoint, endPoint);

	ray.setupWithStartEnd(startPoint, endPoint);
}

void Raycast::drawDebugRaycast(Material& debugMaterial)
{
	drawDebugLineOne.drawLine(debugMaterial, Color::green);

	if (!hit) return;

	drawDebugLineTwo.drawLine(debugMaterial, Color::red);
	drawDebugPointHit.drawPoint(debugMaterial, Color::green);
}

void Raycast::setHitPos(Vector3 hitPosition)
{
	hit = true;

	drawDebugLineOne.setPoints(ray.getStart(), hitPosition);
	drawDebugLineTwo.setPoints(hitPosition, ray.getEnd());
	drawDebugPointHit.setPointPostition(hitPosition);
}

void Raycast::updateDrawDebugTimer(float dt)
{
	if (drawDebugTimer <= 0.0f) return;

	drawDebugTimer -= dt;
	if (drawDebugTimer < 0.0f) drawDebugTimer = 0.0f;
}
