#ifndef _COLOUR_H
#define _COLOUR_H

class Colour
{
public:
	Colour() {}
	Colour(float R, float G, float B):
		m_R(R),
		m_G(G),
		m_B(B),
		m_A(1.0f) {}
	Colour(float R, float G, float B, float A):
		m_R(R),
		m_G(G),
		m_B(B),
		m_A(A) {}

	float m_R;
	float m_G;
	float m_B;
	float m_A;
};
#endif