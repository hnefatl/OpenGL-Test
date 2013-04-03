#include <Windows.h>
#include <GL/GL.h>

#include "Game.h"

Game::Game()
{
	m_RotationAngle=0;
	m_RotationSpeed=0;
}
Game:: Game(float RotationSpeed)
{
	m_RotationAngle=0;
	m_RotationSpeed=RotationSpeed;
}

bool Game::Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

void Game::Update()
{
	m_RotationAngle+=m_RotationSpeed;
	if(m_RotationAngle>360)
	{
		m_RotationAngle-=360;
	}
	if(m_RotationAngle<0)
	{
		m_RotationAngle+=360;
	}
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(m_RotationAngle, 0, 0, 1);
}