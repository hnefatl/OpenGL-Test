#ifndef _WINDOW_H
#define _WINDOW_H

#include <Windows.h>
#include "Game.h"

class Window
{
public:
	Window(HINSTANCE Instance);

	bool Create(const int Width, const int Height, const int BPP, const bool FullScreen);
	void Destroy();
	void ProcessEvents();
	void AttachGame(Game *Game);

	const bool IsRunning();

	static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

	const float GetElapsedSeconds();

private:
	Game *m_Game; // Pointer to game to run
	bool m_IsRunning; // Window is running?
	bool m_IsFullScreen;

	float m_LastTime;

	HWND m_HWND; // Window Handle
	HGLRC m_HGLRC; // Rendering Context
	HDC m_HDC; // Device Context
	RECT m_WindowRect; // Window Boundaries
	HINSTANCE m_HInstance; // App Instance
	WNDCLASSEX m_WindowClass;

	void SetupPixelFormat();
	Game* GetAttachedGame() { return m_Game; }
};

#endif