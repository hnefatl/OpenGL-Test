#include "Vertex.h"

Vertex::Vertex():
	m_X(0),
	m_Y(0),
	m_Z(0)
{
}
Vertex::Vertex(float X, float Y, float Z):
	m_X(X),
	m_Y(Y),
	m_Z(Z)
{
}

const bool Vertex::operator== (const Vertex &One)
{
	return (
		m_X==One.m_X &&
		m_Y==One.m_Y &&
		m_Z==One.m_Z); // All the same attributes
}
const bool Vertex::operator!= (const Vertex &One)
{
	return !operator==(One); // Simple inversion
}