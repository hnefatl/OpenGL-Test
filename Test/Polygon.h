#include <vector>
#include "Colour.h"
#include "Vertex.h"

class Polygon
{
public:
	Polygon(int Points);

	virtual void Update();
	virtual void Render();

private:
	int m_Points;
	std::vector<Vertex> m_Vertices;
	std::vector<Colour> m_Colours;
};