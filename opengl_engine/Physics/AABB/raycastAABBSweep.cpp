#include "raycastAABBSweep.h"

RaycastAABBSweep::RaycastAABBSweep(const Vector3& startPoint, const Vector3& endPoint, const Box& boxInfos, float drawDebugTime, bool loadPersistent) :
	Raycast(drawDebugTime, loadPersistent),
	drawDebugLineOne(), drawDebugLineTwo(), drawDebugCubeOne(), drawDebugCubeTwo(), box(boxInfos)
{
	type = RaycastType::RaycastTypeAABBSweep;

	ray.setupWithStartEnd(startPoint, endPoint);
	box.setCenterPoint(startPoint);

	drawDebugLineOne.setPoints(startPoint, endPoint);
	drawDebugCubeOne.setBox(box);
	drawDebugCubeTwo.setBox(box);
}

void RaycastAABBSweep::drawDebugRaycast(Material& debugMaterial)
{
	drawDebugLineOne.drawLine(debugMaterial, Color::green);
	drawDebugCubeOne.drawCube(debugMaterial, Color::green);
	if (!hit)
	{
		drawDebugCubeTwo.drawCube(debugMaterial, Color::green);
		return;
	}

	drawDebugLineTwo.drawLine(debugMaterial, Color::red);
	drawDebugCubeTwo.drawCube(debugMaterial, Color::red);
}

void RaycastAABBSweep::setValues(bool raycastHit, Vector3 hitPosition)
{
	hit = raycastHit;

	if (raycastHit)
	{
		drawDebugLineOne.setPoints(ray.getStart(), hitPosition);
		drawDebugLineTwo.setPoints(hitPosition, ray.getEnd());

		box.setCenterPoint(hitPosition);
		drawDebugCubeTwo.setBox(box);
	}
	else
	{
		box.setCenterPoint(ray.getEnd());
		drawDebugCubeTwo.setBox(box);
	}
}