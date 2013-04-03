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

}