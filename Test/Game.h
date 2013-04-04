#ifndef _GAME_H
#define _GAME_H

#include "RotatingTriangle.h"

class Game
{
public:
	Game();

	bool Init();
	void Update();
	void Render();
	void Shutdown();

	void OnResize(int Width, int Height);

private:
	RotatingTriangle MainObject;
};

#endif