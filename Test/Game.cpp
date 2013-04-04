#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "Game.h"

Game::Game():
	MainObject(1.0f)
{
}

bool Game::Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

void Game::Update()
{
	MainObject.Update();
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	MainObject.Render();
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