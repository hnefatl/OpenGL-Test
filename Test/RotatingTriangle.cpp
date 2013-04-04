#include <Windows.h>
#include <GL/GL.h>

#include "RotatingTriangle.h"
#include "Vertex.h"
#include "Colour.h"

RotatingTriangle::RotatingTriangle(float RotationSpeed)
	:Polygon(3),
	m_RotationSpeed(RotationSpeed)
{
	for(int x=0; x<3; x++) // Default Data (Blanks)
	{
		m_Vertices.push_back(Vertex());
		m_Colours.push_back(Colour());
	}
}
RotatingTriangle::RotatingTriangle(float RotationSpeed, Vertex One, Vertex Two, Vertex Three)
	:Polygon(3),
	m_RotationSpeed(RotationSpeed)
{
	m_Vertices.push_back(One);
	m_Vertices.push_back(Two);
	m_Vertices.push_back(Three);

	for(int x=0; x<3; x++) // Default Colours (Blanks)
	{
		m_Colours.push_back(Colour());
	}
}
RotatingTriangle::RotatingTriangle(float RotationSpeed, Vertex VOne, Colour COne, Vertex VTwo, Colour CTwo, Vertex VThree, Colour CThree)
	:Polygon(3),
	m_RotationSpeed(RotationSpeed)
{
	m_Vertices.push_back(VOne);
	m_Colours.push_back(COne);
	m_Vertices.push_back(VTwo);
	m_Colours.push_back(CTwo);
	m_Vertices.push_back(VThree);
	m_Colours.push_back(CThree);
}

void RotatingTriangle::Update()
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
}
void RotatingTriangle::Render()
{
	glBegin(GL_TRIANGLES);
	for(unsigned int x=0; x<m_Vertices.size(); x++)
	{
		glColor4f(m_Colours[x].m_R, m_Colours[x].m_G, m_Colours[x].m_B, m_Colours[x].m_A);
		glVertex3f(m_Vertices[x].m_X, m_Vertices[x].m_Y, m_Vertices[x].m_Z); 
	}
	glEnd();
}