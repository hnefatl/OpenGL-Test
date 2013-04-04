#include <Windows.h>
#include <GL/GL.h>

#include "RotatingPolygon.h"

RotatingPolygon::RotatingPolygon(float RotationSpeed)
	:Polygon(),
	m_RotationSpeed(RotationSpeed),
	m_RotationAngle(0)
{
}

RotatingPolygon::~RotatingPolygon()
{
}

void RotatingPolygon::Update(float ElapsedTime)
{
	m_RotationAngle+=m_RotationSpeed;
	if(m_RotationAngle>360)
	{
		m_RotationAngle-=360;
	}
	if(m_RotationAngle<0)
	{
		m_RotationAngle+=360;
	}

	glRotatef(m_RotationAngle, 0, 0, 1);
}

void RotatingPolygon::Render()
{
	glRotatef(m_RotationAngle, 0, 0, 1);
	Polygon::Render();
}