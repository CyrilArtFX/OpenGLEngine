#include "raycastAABBSweep.h"

RaycastAABBSweep::RaycastAABBSweep(const Vector3& startPoint, const Vector3& endPoint, const Box& boxInfos, float drawDebugTime, bool loadPersistent) :
	Raycast(drawDebugTime, loadedPersistent),
	drawDebugLineOne(), drawDebugLineTwo(), drawDebugCube(), box(boxInfos), baseBoxInfos(boxInfos)
{
	type = RaycastType::RaycastTypeAABBSweep;

	ray.setupWithStartEnd(startPoint, endPoint);
	box.setCenterPoint(baseBoxInfos.getCenterPoint() + startPoint);

	drawDebugLineOne.setPoints(startPoint, endPoint);
	drawDebugCube.setBox(box);
}

void RaycastAABBSweep::drawDebugRaycast(Material& debugMaterial)
{
	drawDebugLineOne.drawLine(debugMaterial, Color::green);
	if (!hit)
	{
		drawDebugCube.drawCube(debugMaterial, Color::green);
		return;
	}

	drawDebugLineTwo.drawLine(debugMaterial, Color::red);
	drawDebugCube.drawCube(debugMaterial, Color::red);
}

void RaycastAABBSweep::setValues(bool raycastHit, Vector3 hitPosition)
{
	hit = raycastHit;

	if (raycastHit)
	{
		drawDebugLineOne.setPoints(ray.getStart(), hitPosition);
		drawDebugLineTwo.setPoints(hitPosition, ray.getEnd());

		box.setCenterPoint(baseBoxInfos.getCenterPoint() + hitPosition);
		drawDebugCube.setBox(box);
	}
	else
	{
		box.setCenterPoint(baseBoxInfos.getCenterPoint() + ray.getEnd());
		drawDebugCube.setBox(box);
	}
}