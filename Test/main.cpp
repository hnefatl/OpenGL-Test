#include <iostream>

#ifndef _WIN32
int main(int argc, char* argv[])
{
	std::cerr<<"Invalid OS. Only Windows is supported."<<std::endl;
	return 0;
}
#endif

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define GLX_GLXEXT_LEGACY

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
	const int WINDOW_WIDTH=1024;
	const int WINDOW_HEIGHT=768;
	const int WINDOW_BPP=16;
	const bool WINDOW_FULLSCREEN=false;

	Window GameWindow(instance);
	Game GLGame;

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
	float ElapsedTime = 0;
	while(GameWindow.IsRunning())
	{
		GameWindow.ProcessEvents();

		ElapsedTime=GameWindow.GetElapsedSeconds();

		GLGame.Update(ElapsedTime); // Update logic
		GLGame.Render(); // Render scene

		GameWindow.FlipBuffers();
	}

	GLGame.Shutdown(); // Free resources
	GameWindow.Destroy(); // Clean up window

	return 0;
}
#endif