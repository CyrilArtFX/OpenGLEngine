#include "raycast.h"

Raycast::Raycast(const Vector3& startPoint, const Vector3& endPoint) : drawDebugLineOne(), drawDebugLineTwo(), drawDebugPointHit()
{
	drawDebugLineOne.setPoints(startPoint, endPoint);

	ray.start = startPoint;
	ray.end = endPoint;
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

	drawDebugLineOne.setPoints(ray.start, hitPosition);
	drawDebugLineTwo.setPoints(hitPosition, ray.end);
	drawDebugPointHit.setPointPostition(hitPosition);
}
