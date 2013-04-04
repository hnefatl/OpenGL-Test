#ifndef _POLYGON_H
#define _POLYGON_H
#include <vector>
#include "Colour.h"
#include "Vertex.h"

class Polygon
{
public:
	Polygon(int Points);

	virtual void Update();
	virtual void Render();

	virtual void AddVertex(Vertex Point);
	virtual void AddVertex(Vertex Point, Colour Colour);
	virtual void RemoveVertex(int Number);
	virtual void RemoveVertex(Vertex Point);

	virtual Vertex &GetVertex(int Number);

protected:
	int m_Points;
	std::vector<Vertex> m_Vertices;
	std::vector<Colour> m_Colours;
};
#endif