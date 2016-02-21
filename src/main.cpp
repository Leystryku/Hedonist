#include "main.h"

mainclass *Main = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	if (message == WM_CLOSE)
		PostQuitMessage(0);

	return DefWindowProc(hWnd, message, wParam, lParam);

}

int CreateGameWindow()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	Main->MonitorWidth = desktop.right;
	Main->MonitorHeight = desktop.bottom;


	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = 0;

	wc.lpszClassName = L"hedonist_class";
	if (!RegisterClass(&wc))
	{
		return 1;
	}
	Main->window_x = (Main->MonitorWidth / 2) - (Main->window_Width / 2);
	Main->window_y = (Main->MonitorHeight / 2) - (Main->window_Height / 2);

	if (!(Main->window_handle = CreateWindow(wc.lpszClassName,
		L"Hedonist",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		Main->window_x, Main->window_y, Main->window_Width, Main->window_Height, 0, 0, 0, NULL)))
	{
		return 2;
	}



	if (Main->window_NoBorder)
	{
		SetWindowLong(Main->window_handle, GWL_STYLE, 0);
		ShowWindow(Main->window_handle, SW_SHOW);
	}

	std::string init = d3d->Initiate(Main->window_handle, Main->window_Width, Main->window_Height);

	if (init != "")
	{
		MessageBoxA(NULL, init.c_str(), "Init error!", MB_OK);
		return 3;
	}

	if (!d3d || !d3d->instance)
	{
		return 4;
	}

	menu->Initialize(Main->window_Width, Main->window_Height);

	return 0;
}

void WindowThink()
{
	MSG msg = { 0 };
	menu->is_open = true;

	while (true)
	{
		if (Main->ExitMain)
		{
			break;
		}

		static unsigned lastTime;
		unsigned time, dt;

		if (Main->MinDT)
		{


			do {


				if (PeekMessage(&msg, Main->window_handle, 0, 0, false)>0)
				{
					if (msg.message == WM_QUIT)
						Main->ExitMain = true;
					TranslateMessage(&msg);
					if (msg.message == WM_QUIT)
						Main->ExitMain = true;
					DispatchMessage(&msg);
				}



				time = timeGetTime();
				if (!lastTime) {
					lastTime = time;
				}
				dt = time - lastTime;


			} while (dt < Main->MinDT);

			lastTime = time;

		}
		else{
			if (PeekMessage(&msg, Main->window_handle, 0, 0, false)>0)
			{
				if (msg.message == WM_QUIT)
					Main->ExitMain = true;
				TranslateMessage(&msg);
				if (msg.message == WM_QUIT)
					Main->ExitMain = true;
				DispatchMessage(&msg);
			}



		}

		GameLogic::DoThink();
		Drawing::DoThink(false);
		Sounds::DoThink();

		//std::cout << "DO THINK";




	}

}
void mainclass::Main()
{
	menu = new m_menu;
	d3d = new m_d3d;

	int error = CreateGameWindow();

	if (error)
		MessageBoxA(NULL, "an error occured while creating the game window!", "Hedonist", MB_OK);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WindowThink, 0, 0, 0);


	std::cin.get();
}

int main(int argc, char* argv[])
{
	Main = new mainclass;

	Main->pathToExe = argv[0];

	if (argc >= 1 && argv[1])
		Main->window_Width = atoi(argv[1]);
	else
		Main->window_Width = 720;

	if (argc >= 2 && argv[2])
		Main->window_Height = atoi(argv[2]);
	else
		Main->window_Height = 480;

	if (argc >= 3 && argv[3])
		Main->MaxFps = (float)atoi(argv[3]);

	if (Main->MaxFps > 0)
		Main->MinDT = (1000 / (Main->MaxFps));

	if (argc >= 4 && argv[4] && strstr(argv[4], "-noborder"))
		Main->window_NoBorder = true;

	Main->Main();
	return 0;
}