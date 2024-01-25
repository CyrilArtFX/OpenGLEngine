#include "line.h"
#include <glad/glad.h>
#include <vector>
#include <iostream>

Line::Line()
{
	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);
	glBindVertexArray(0);

	std::cout << "Creating Line\n";
}

Line::~Line()
{
	glDeleteVertexArrays(1, &lineVAO);
	glDeleteBuffers(1, &lineVBO);

	std::cout << "Destroying Line\n";
}

void Line::setPoints(Vector3 pointA, Vector3 pointB)
{
	std::vector<Vector3> points{ pointA, pointB };

	glBindVertexArray(lineVAO); //  bind the VAO before binding the vertex buffer, and before configuring vertex attributes 

	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vector3), &points[0], GL_STATIC_DRAW);

	//  position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(0);

	//  unbind vertex array
	glBindVertexArray(0);
}

void Line::drawLine(Material& debugMaterial, const Color& drawColor)
{
	debugMaterial.getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());
	debugMaterial.getShader().setVec3("color", drawColor);
	
	glBindVertexArray(lineVAO);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
}