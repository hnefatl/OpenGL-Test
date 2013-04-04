#include <windows.h>
#include <GL/GL.h>
#include <vector>

#include "Polygon.h"
#include "Vertex.h"

Polygon::Polygon(int Points):
	m_Points(Points),
	m_Vertices(Points),
	m_Colours(Points)
{
}

void Polygon::Update()
{

}
void Polygon::Render()
{
	glBegin(GL_POLYGON);
	for(int x=0; x<m_Vertices.size(); x++)
	{
		glColor4f(m_Colours[x].m_R, m_Colours[x].m_G, m_Colours[x].m_B, m_Colours[x].m_A);
		glVertex3f(m_Vertices[x].m_X, m_Vertices[x].m_Y, m_Vertices[x].m_Z); 
	}
	glEnd();
}

void Polygon::AddVertex(Vertex Point)
{
	m_Vertices.push_back(Point); // Add Vertex
	m_Colours.push_back(Colour(1.0, 1.0, 1.0)); // Add "White"
	++m_Points;
}
void Polygon::AddVertex(Vertex Point, Colour Colour)
{
	m_Vertices.push_back(Point);
	m_Colours.push_back(Colour);
	++m_Points;
}
void Polygon::RemoveVertex(int Number)
{
	m_Vertices.erase(m_Vertices.begin()+Number);
	m_Colours.erase(m_Colours.begin()+Number);
	--m_Points;
}
void Polygon::RemoveVertex(Vertex Point)
{
	for(int x=0; x<m_Vertices.size(); x++)
	{
		if(m_Vertices[x]==Point)
		{
			m_Vertices.erase(m_Vertices.begin()+x);
			m_Colours.erase(m_Colours.begin()+x);
			--m_Points;
			break;
		}
	}
}

Vertex &Polygon::GetVertex(int Number)
{
	return m_Vertices[Number];
}