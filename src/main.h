#pragma once

#include "includes.h"
#include "gamelogic/gamelogic.h"
#include "drawing/drawing.h"
#include "menu/menu.h"
#include "sounds/sounds.h"

class mainclass
{
public:
	void Main();
	
	bool ExitMain = false;

	const char *pathToExe = "";
	int MonitorWidth = 0;
	int MonitorHeight = 0;

	float MaxFps = 0;
	float MinDT = 0;


	
	int window_x = 0;
	int window_y = 0;
	int window_Width = 0;
	int window_Height = 0;
	bool window_NoBorder = false;
	HWND window_handle = 0;


};


extern mainclass *Main;