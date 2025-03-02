#include "raycastLine.h"

RaycastLine::RaycastLine(const Vector3& startPoint, const Vector3& endPoint, float drawDebugTime, bool loadPersistent) :
	Raycast(drawDebugTime, loadPersistent),
	drawDebugLineOne(), drawDebugLineTwo(), drawDebugPointHit()
{
	type = RaycastType::RaycastTypeLine;

	drawDebugLineOne.setPoints(startPoint, endPoint);

	ray.setupWithStartEnd(startPoint, endPoint);
}


void RaycastLine::drawDebugRaycast(Material& debugMaterial)
{
	drawDebugLineOne.drawLine(debugMaterial, Color::green);

	if (!hit) return;

	drawDebugLineTwo.drawLine(debugMaterial, Color::red);
	drawDebugPointHit.drawPoint(debugMaterial, Color::green);
}

void RaycastLine::setHitPos(Vector3 hitPosition)
{
	hit = true;

	drawDebugLineOne.setPoints(ray.getStart(), hitPosition);
	drawDebugLineTwo.setPoints(hitPosition, ray.getEnd());
	drawDebugPointHit.setPointPostition(hitPosition);
}
