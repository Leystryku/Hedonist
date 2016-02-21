#pragma once

#include "../includes.h"
#include <d3d9.h>
#include <d3dx9.h>
//#include "menu.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class m_d3d
{
public:

	void DrawText(std::string pString, int x, int y, D3DCOLOR col, ID3DXFont *font, DWORD format = NULL, int w = NULL, int h = NULL);

	void DrawTextW(LPCWSTR pString, int len, int x, int y, D3DCOLOR col, ID3DXFont *font, DWORD format = NULL, int w = NULL, int h = NULL);

	void DrawRectangle(int x, int y, int w, int h, D3DCOLOR BoxColor);

	void DrawOutlinedRectangle(int x, int y, int w, int h, int thickness, D3DCOLOR BoxColor, D3DCOLOR BorderColor);

	void DrawLine(float x, float y, float x2, float y2, float thickness, D3DCOLOR LineCol);

	D3DXVECTOR2 GetTextSize(ID3DXFont* font, const char*txt);


	std::string Initiate(HWND hWnd, int ScrW, int ScrH);

	bool bFlushDraw = false;

	LPD3DXFONT font1;
	LPD3DXFONT font2;
	LPD3DXFONT font3;
	LPD3DXFONT font4;
	LPD3DXFONT font5;

	LPD3DXSPRITE sprite;
	ID3DXLine *line;

	IDirect3DDevice9Ex *device;
	IDirect3D9Ex *instance;

	int scrw, scrh;

};

extern m_d3d *d3d;