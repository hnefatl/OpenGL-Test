#include <windows.h>
#include <GL/GL.h>
#include <vector>
#include "Polygon.h"

Polygon::Polygon(int Points)
{
	m_Points=Points;
	m_Vertices=std::vector<Vertex>(Points);
	m_Colours=std::vector<Colour>(Points);
}

void Polygon::Update()
{

}

void Polygon::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	for(int x=0; x<m_Vertices.size(); x++)
	{
		glColor4f(m_Colours[x].m_R, m_Colours[x].m_G, m_Colours[x].m_B, m_Colours[x].m_A);
		glVertex3f(m_Vertices[x].m_X, m_Vertices[x].m_Y, m_Vertices[x].m_Z); 
	}
	glEnd();
}