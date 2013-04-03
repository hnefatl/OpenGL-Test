#include "Window.h"

Window::Window(HINSTANCE Instance):
	m_IsRunning(false),
	m_Game(NULL),
	m_HInstance(Instance),
	m_LastTime(0)
{

}

bool Window::Create(const int Width, const int Height, const int BPP, const bool Fullscreen)
{
	DWORD WinExStyle;
	DWORD WinStyle;

	m_IsFullScreen=Fullscreen;

	// Set window size
	m_WindowRect.left=0;
	m_WindowRect.right=Width;
	m_WindowRect.top=0;
	m_WindowRect.bottom=Height;

	// Window Class structure
	m_WindowClass.cbSize			=sizeof(WNDCLASSEX);
	m_WindowClass.style				=CS_HREDRAW|CS_VREDRAW;
	m_WindowClass.lpfnWndProc		=Window::StaticWndProc; // Static method set as event handler
	m_WindowClass.cbClsExtra		=0;
	m_WindowClass.cbWndExtra		=0;
	m_WindowClass.hInstance			=m_HInstance;
	m_WindowClass.hIcon				=LoadIcon(NULL, IDI_APPLICATION);
	m_WindowClass.hCursor			=LoadCursor(NULL, IDC_ARROW);
	m_WindowClass.hbrBackground		=NULL;
	m_WindowClass.lpszMenuName		=NULL;
	m_WindowClass.lpszClassName		=NULL;
	m_WindowClass.hIconSm			=LoadIcon(NULL, IDI_WINLOGO);

	// Attempt to register WIndow Class
	if(!RegisterClassEx(&m_WindowClass))
	{
		return false;
	}

	if(m_IsFullScreen) // If fullscreen, change display mode
	{
		DEVMODE ScreenSettings;

		memset(&ScreenSettings, 0, sizeof(ScreenSettings));
		ScreenSettings.dmSize=sizeof(ScreenSettings);

		ScreenSettings.dmPelsWidth		=Width;
		ScreenSettings.dmPelsHeight		=Height;
		ScreenSettings.dmBitsPerPel		=BPP;
		ScreenSettings.dmFields			=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// Display mode alteration failed; switch to windowed as backup
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			m_IsFullScreen=false;
		}
	}

	if(m_IsFullScreen)
	{
		// Still in fullscreen mode (succesful change)
		WinExStyle=WS_EX_APPWINDOW;
		WinStyle=WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		WinExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
		WinStyle=WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&m_WindowRect, WinStyle, false, WinExStyle); // Adjust window to true size

	// Class registered, now create window
	m_HWND=CreateWindowEx(
		NULL,										// Window Extended Style
		"GLClass",									// Class Name
		"Test",										// App Name
		WinStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,	// Window Style
		0,											// X
		0,											// Y
		m_WindowRect.right-m_WindowRect.left,		// Width
		m_WindowRect.bottom-m_WindowRect.top,		// Height
		NULL,										//Parent Handle
		NULL,										// Menu Handle
		m_HInstance,								// Application Instance,
		this);										// Pointer to this Window

	if(!m_HWND)
	{
		// Window creation failed (NULL)
		return 1;
	}

	m_HDC=GetDC(m_HWND); // Get Device Context
	ShowWindow(m_HWND, SW_SHOW); // Display Window
	UpdateWindow(m_HWND); // Update Window

	m_LastTime=GetTickCount()/1000.0f; // Initialize time

	return true;
}