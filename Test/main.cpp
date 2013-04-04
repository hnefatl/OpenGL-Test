#include <iostream>

#ifndef _WIN32
int main(int argc, char* argv[])
{
	std::cerr<<"Invalid OS. Only Windows is supported."<<std::endl;
	return 0;
}
#endif

#ifdef _WIN32
#include <windows.h>
#include <GL/GL.h>

#include "Window.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE instance,
				   HINSTANCE previnstance,
				   LPSTR cmdline,
				   int cmdshow)
{
	// Window settings
	const int WINDOW_HEIGHT=700;
	const int WINDOW_WIDTH=700;
	const int WINDOW_BPP=16;
	const bool WINDOW_FULLSCREEN=false;

	Window GameWindow=Window(instance);
	Game GLGame=Game();

	GameWindow.AttachGame(&GLGame);

	if(!GameWindow.Create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOW_FULLSCREEN))
	{
		// Failed window creation
		MessageBox(NULL, "Unable to create window.", "Error", MB_ICONERROR|MB_OK);
		GameWindow.Destroy();
	}

	if(!GLGame.Init())
	{
		// Failed to initialise game
		MessageBox(NULL, "Unable to create game.", "Error", MB_ICONERROR|MB_OK);
		GameWindow.Destroy();
	}

	// Main Game Loop
	while(GameWindow.IsRunning())
	{
		GameWindow.ProcessEvents();

		GLGame.Update(); // Update logic
		GLGame.Render(); // Render scene

		GameWindow.FlipBuffers();
	}

	GLGame.Shutdown(); // Free resources
	GameWindow.Destroy(); // Clean up window

	return 0;
}
#endif