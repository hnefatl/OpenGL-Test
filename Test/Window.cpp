#include <iostream>
#include <Windows.h>
#include <GL/GL.h>

#include "Window.h"
#include "wglext.h"

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

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

void Window::Destroy()
{
	if(m_IsFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}
}

void Window::AttachGame(Game *Game)
{
	m_Game=Game;
}

const bool Window::IsRunning()
{
	return m_IsRunning;
}

void Window::ProcessEvents()
{
	MSG msg;

	// Work on message
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::SetupPixelFormat()
{
	int PixelFormat;

	PIXELFORMATDESCRIPTOR PFD=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size
		1,								// Version
		PFD_SUPPORT_OPENGL|				// OpenGL Window
		PFD_DRAW_TO_WINDOW|				// Rendering to window
		PFD_DOUBLEBUFFER|				// Double-buffering support
		PFD_TYPE_RGBA,					// Colour type
		32,								// Preferred colour depth
		0, 0, 0, 0, 0, 0,				// Colour bits (ignored)
		0,								// No Alpha buffer
		0,								// Alpha bits (ignored)
		0,								// No accumulation buffer
		0, 0, 0, 0,						// Accumulated bits (ignored)
		16,								// Depth buffer
		0,								// No stencil buffer
		0,								// No auxilary buffers
		PFD_MAIN_PLANE,					// Main layer
		0,								// Reserved
		0, 0, 0,						// No layer, visible, damage masks
	};

	PixelFormat=ChoosePixelFormat(m_HDC, &PFD);
	SetPixelFormat(m_HDC, PixelFormat, &PFD);
}

LRESULT Window::WndProc(HWND hwnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	switch(Msg)
	{
	case WM_CREATE: // Window creation
		{
			m_HDC=GetDC(hwnd);
			SetupPixelFormat();

			// Set OpenGL version we want
			int attribs[]=
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 0,
				0, // End of array
			};

			// Create temporary context using deprecated function to get pointer to function
			HGLRC TempContext=wglCreateContext(m_HDC);
			// Make it current
			wglMakeCurrent(m_HDC, TempContext);

			// Get pointer to function
			wglCreateContextAttribsARB=(PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

			// If NULL, OpenGL 3.0 isn't supported
			if(!wglCreateContextAttribsARB)
			{
				std::cerr<<"OpenGL 3.0 is not supported. Falling back to GL 2.1."<<std::endl; // Simple write
				m_HGLRC=TempContext;
			}
			else 
			{
				// Create OpenGL 3.0 funtion
				m_HGLRC=wglCreateContextAttribsARB(m_HDC, 0, attribs);
				// Delete temporary context
				wglDeleteContext(TempContext);
			}

			// Make OpenGL Context current
			wglMakeCurrent(m_HDC, m_HGLRC);

			m_IsRunning=true; // Set running flag
		}
	break;

	case WM_DESTROY:
	case WM_CLOSE:
		{
			// On closing or destruction
			wglMakeCurrent(m_HDC, NULL);
			wglDeleteContext(m_HGLRC);
			m_IsRunning=false;
			PostQuitMessage(0);
			return 0;
		}
	break;

	case WM_SIZE: 
		{
			int Height=HIWORD(lparam);
			int Width=LOWORD(lparam);
			// GetAttachedGame()->OnResize(Width, Height);
		}
	break;

	case WM_KEYDOWN:
		{
			if(wparam==VK_ESCAPE) // If escape key pressed
			{
				DestroyWindow(m_HWND); // Send a WM_DESTROY message
			}
		}
	break;
	default:
	break;
	}

	return DefWindowProc(hwnd, Msg, wparam, lparam);
}

LRESULT Window::StaticWndProc(HWND hwnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	Window *window=NULL;

	// If thi is the creation message
	if(Msg==WM_CREATE)
	{
		// Get the pointer we stored during call to Window::Create
		window=(Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;

		// Associate window pointer to hwnd for other events to access
		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)window);
	}
	else 
	{
		// If not the creation event, we have a stored pointer to the window
		window=(Window*)GetWindowLongPtr(hwnd, GWL_USERDATA);

		if(!window)
		{
			return DefWindowProc(hwnd, Msg, wparam, lparam);
		}
	}

	// Call window's member WndProc (allowing us to access member variables)
	return window->WndProc(hwnd, Msg, lparam, wparam);
}

float Window::GetElapsedSeconds()
{
	float CurrentTime=float(GetTickCount())/1000.0f;
	float Seconds=float(CurrentTime-m_LastTime);
	m_LastTime=CurrentTime;
	return Seconds;
}