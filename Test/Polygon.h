#ifndef _POLYGON_H
#define _POLYGON_H
#include <vector>

class Polygon
{
public:
	Polygon();
	virtual ~Polygon();

	virtual void Update(float ElapsedTime);
	virtual void Render();

	void AddVertex(float X, float Y, float Z);
	void AddVertex(float X, float Y, float Z, float R, float G, float B);

protected:
	std::vector<float> m_Vertices;
	std::vector<float> m_Colours;
};
#endif