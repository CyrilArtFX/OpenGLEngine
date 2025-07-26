#include "line.h"
#include <Maths/Matrix4.h>
#include <Rendering/Model/vertexArray.h>
#include <Assets/assetManager.h>

Line::Line() : lineVA(AssetManager::GetVertexArray("debug_line"))
{
}

Line::~Line()
{
}

void Line::setPoints(Vector3 pointA, Vector3 pointB)
{
	originPos = pointA;
	pointOffset = pointB - pointA;
}

void Line::draw(Material& debugMaterial, const Color& drawColor)
{
	Shader& debug_shader = debugMaterial.getShader();
	debug_shader.setMatrix4("model", Matrix4::createTranslation(originPos).getAsFloatPtr());
	debug_shader.setVec3("color", drawColor);
	debug_shader.setBool("renderLine", true);
	debug_shader.setVec3("linePointOffset", pointOffset);

	lineVA.setActive();
	glDrawArrays(GL_LINE_STRIP, 0, 2);

	debug_shader.setBool("renderLine", false);
}