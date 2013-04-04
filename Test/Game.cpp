#include <Windows.h>
#include <GL/GL.h>

#include "Game.h"

Game::Game():
	MainObject(15.0f)
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

