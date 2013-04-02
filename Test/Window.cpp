#include "Window.h"

Window::Window(HINSTANCE Instance):
	m_IsRunning(false),
	m_Game(NULL),
	m_HInstance(Instance),
	m_LastTime(0)
{

}