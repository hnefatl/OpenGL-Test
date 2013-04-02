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
	Game *m_Game;
	bool m_IsRunning;
	bool m_IsFullScreen;

	float m_LastTime;

	HWND m_HWEND;
	HGLRC m_HGLRC;
	HDC m_HDC;
	RECT m_WindowRect;
	HINSTANCE m_HInstance;
	WNDCLASSEX m_WindowClass;

	void SetupPixelFormat();
	Game* GetAttachedGame() { return m_Game; }
};

#endif