#ifndef _GAME_H
#define _GAME_H

#include "RotatingPolygon.h"

class Game
{
public:
	Game();
	Game(int FPS);

	bool Init();
	void Update(float ElapsedTime);
	void Render();
	void Shutdown();

	bool HandleInput (WPARAM Data);

	void OnResize(int Width, int Height);

private:
	RotatingPolygon MainObject;
	int m_FPS;
};

#endif