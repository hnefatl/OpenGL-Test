#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "Game.h"

Game::Game():
	MainObject(100.0f),
	m_FPS(10)
{
}
Game::Game(int FPS):
	MainObject(100.0f),
	m_FPS(FPS)
{
}

bool Game::Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	MainObject.AddVertex(0 ,  1,  -4,		1, 0, 0);		// Top
	MainObject.AddVertex(-1, -1,  -4,		0, 1, 0);	// Bottom-Left
	MainObject.AddVertex(1 , -1,  -4,		0, 0, 1);	// Bottom-Right

	return true;
}

void Game::Update(float ElapsedTime)
{
	MainObject.Update(ElapsedTime);
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	MainObject.Render();
}

bool Game::HandleInput(WPARAM Data)
{
	if(Data==VK_ESCAPE) // If escape key pressed
	{
		return false;
	}
	else if(Data==VK_UP)
	{
		MainObject.GetRotationSpeed()+=10.0f;
	}
	else if(Data==VK_DOWN)
	{
		MainObject.GetRotationSpeed()-=10.0f;
	}
	else if(Data==VK_LEFT)
	{
		MainObject.GetRotationSpeed()-=1.0f;
	}
	else if(Data==VK_RIGHT)
	{
		MainObject.GetRotationSpeed()+=1.0f;
	}

	return true;
}

void Game::Shutdown()
{

}

void Game::OnResize(int Width, int Height)
{
	glViewport(0, 0, Width, Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, float(Width)/float(Height), 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}