#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "Polygon.h"

class RotatingTriangle:
	Polygon
{
public:
	RotatingTriangle(float RotationSpeed);
	RotatingTriangle(float RotationSpeed, Vertex One, Vertex Two, Vertex Three);
	RotatingTriangle(float RotationSpeed, Vertex VOne, Colour COne, Vertex VTwo, Colour CTwo, Vertex VThree, Colour CThree); 
	
	void Update(); // Override superclass Polygon's default updater
	void Render(); // Override superclass Polygon's default renderer

protected:
	float m_RotationAngle;
	float m_RotationSpeed;
};
#endif