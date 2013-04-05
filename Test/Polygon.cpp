#include <windows.h>
#include <GL/GL.h>
#include <vector>

#include "Polygon.h"

Polygon::Polygon()
{
}
Polygon::~Polygon()
{
}

void Polygon::Update(float ElapsedTime)
{

}
void Polygon::Render()
{
	// Enable polygonal and colour drawing
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Load stored vertices and colours
	glVertexPointer(3, GL_FLOAT, 0, &m_Vertices[0]);
	glColorPointer(3, GL_FLOAT, 0, &m_Colours[0]);

	// Draw vertices
	glDrawArrays(GL_POLYGON, 0, 3);

	// Disable client states
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Polygon::AddVertex(float X, float Y, float Z)
{
	// Add Vertices
	m_Vertices.push_back(X);
	m_Vertices.push_back(Y);
	m_Vertices.push_back(Z);
	// Add colours
	m_Colours.push_back(1);
	m_Colours.push_back(1);
	m_Colours.push_back(1);
}
void Polygon::AddVertex(float X, float Y, float Z, float R, float G, float B)
{
	// Add vertices
	m_Vertices.push_back(X);
	m_Vertices.push_back(Y);
	m_Vertices.push_back(Z);
	// Add colours
	m_Colours.push_back(R);
	m_Colours.push_back(G);
	m_Colours.push_back(B);
}