#ifndef _VERTEX_H
#define _VERTEX_H

class Vertex
{
public:
	Vertex();
	Vertex(float X, float Y, float Z);

	const bool operator== (const Vertex &One);
	const bool operator!= (const Vertex &One);

	float m_X;
	float m_Y;
	float m_Z;
};
#endif