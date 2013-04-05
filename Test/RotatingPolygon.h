#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "Polygon.h"

class RotatingPolygon:
	public Polygon
{
public:
	RotatingPolygon(float RotationSpeed);
	virtual ~RotatingPolygon();
	
	virtual void Update(float ElapsedTime); // Override superclass Polygon's default updater
	virtual void Render(); // Override superclass Polygon's default renderer

	float &GetRotationSpeed();

protected:
	float m_RotationAngle;
	float m_RotationSpeed;
};
#endif