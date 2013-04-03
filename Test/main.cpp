#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <GL/GL.h>

#include "Window.h"
#endif

int main(int argc, char* argv[])
{
	#ifndef _WIN32
	std::cerr<<"Invalid OS. Only Windows is supported."<<std::endl;
	#endif
	const int WINDOW_HEIGHT=700;
	const int WINDOW_WIDTH=700;
	const int WINDOW_BPP=32;
	const bool WINDOW_FULLSCREEN=false;
}