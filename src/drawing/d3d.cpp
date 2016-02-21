#pragma once

#include "d3d.h"


m_d3d *d3d = new m_d3d;

inline const wchar_t *tounicode(const char *text, int &length)
{
	wchar_t buf[64] = { 0 };
	wchar_t *p = buf;

	for (; *text;)
	{
		register char t = *text++;

		if (t < 0x80)
		{
			*p++ = t;
		}
		else
		{
			*p++ = ((t & 0x1f) << 6) | (*text++ & 0x3f);
		}
	}

	length = p - buf;

	return buf;
}


void m_d3d::DrawText(std::string pString, int x, int y, D3DCOLOR col, ID3DXFont *font, DWORD format, int w, int h)
{
	if (!device)
		return;

	if (!font)
		return;


	RECT FontRect = { (int)x, (int)y, (int)x, (int)y };

	if (w && h)
	{
		FontRect = { (int)x, (int)y, (int)(w + x), (int)(h + y) };
	}

	if (format)
	{
		font->DrawTextA(NULL, pString.c_str(), pString.length(), &FontRect, format, col);
		return;
	}
	
	font->DrawTextA(NULL, pString.c_str(), pString.length(), &FontRect, DT_NOCLIP, col);

}

void m_d3d::DrawTextW(LPCWSTR pString, int len, int x, int y, D3DCOLOR col, ID3DXFont *font, DWORD format, int w, int h)
{
	if (!device)
		return;

	if (!font)
		return;

	RECT FontRect = { (int)x, (int)y, (int)x, (int)y };

	if (w && h)
	{
		FontRect = { (int)x, (int)y, (int)(w + x), (int)(h + y) };
	}

	
	if (format)
	{
		font->DrawTextW(NULL, pString, len, &FontRect, format, col);
		return;
	}
	
	font->DrawTextW(NULL, pString, len, &FontRect, DT_NOCLIP, col);

}

class CVertexList
{
public:
	FLOAT X, Y, Z;
	DWORD dColor;
};

void m_d3d::DrawRectangle(int x, int y, int w, int h, D3DCOLOR BoxColor)
{

	CVertexList VertexList[4] =
	{
		{ (float)x, (float)y + (float)h, 0.0f, BoxColor },
		{ (float)x, (float)y, 0.0f, BoxColor },
		{ (float)x + (float)w, (float)y + (float)h, 0.0f, BoxColor },
		{ (float)x + (float)w, (float)y, 0.0f, BoxColor },
	};

	device->SetTexture(0, NULL);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, VertexList, sizeof(CVertexList));
}

void m_d3d::DrawOutlinedRectangle(int x, int y, int w, int h, int thickness, D3DCOLOR BoxColor, D3DCOLOR BorderColor)
{
	DrawRectangle(x, y, w, h, BoxColor);

	//Top horiz line
	DrawRectangle(x, y, w, thickness, BorderColor);
	//Left vertical line
	DrawRectangle(x, y, thickness, h, BorderColor);
	//right vertical line
	DrawRectangle((x + w), y, thickness, h, BorderColor);
	//bottom horiz line
	DrawRectangle(x, y + h, w + thickness, thickness, BorderColor);

}

void m_d3d::DrawLine(float x, float y, float x2, float y2, float thickness, D3DCOLOR LineCol)
{

	CVertexList VertexList[2] =
	{
		{ (float)x, (float)y, 0.0f, LineCol },
		{ (float)x2, (float)y2, 0.0f, LineCol },
	};

	device->SetTexture(0, NULL);
	device->DrawPrimitiveUP(D3DPT_LINELIST, 2, VertexList, sizeof(CVertexList));

	if (thickness && thickness > 1.f)
	{
		int thick = (int)thickness;

		for (int i = 1; i < thick; i++)
		{
			DrawLine(x, y + i, x2, y2 + i, 0, LineCol);
		}
	}
	

}


D3DXVECTOR2 m_d3d::GetTextSize(ID3DXFont* font, const char* txt)
{

	RECT _recA;

	_recA.left = 0;
	_recA.top = 0;
	_recA.bottom = 500;
	_recA.right = 500;

	// this does not render to screen
	font->DrawTextA(NULL, txt, -1, &_recA, DT_CALCRECT, D3DCOLOR_RGBA(0, 0, 0, 0));

	D3DXVECTOR2 size;
	size.x = (float)_recA.right;
	size.y = (float)_recA.bottom;

	return size;
}

std::string m_d3d::Initiate(HWND hWnd, int ScrW, int ScrH)
{

	if (!hWnd)
		return "Invalid hWnd!\n";

	HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &instance);

	if (FAILED(hr))
		return "Couldn't create instance!\n";

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;     // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = ScrW;    // set the width of the buffer
	d3dpp.BackBufferHeight = ScrH;    // set the height of the buffer
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT res = instance->CreateDeviceEx(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		NULL,
		&device);

	if (FAILED(res))
		return "Couldn't create device!\n";

	D3DXCreateSprite(device, &sprite);
	D3DXCreateLine(device, &line);

	D3DXCreateFontA(device, 7, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font1);
	D3DXCreateFontA(device, 15, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font2);
	D3DXCreateFontA(device, 20, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font3);
	D3DXCreateFontA(device, 28, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font4);
	D3DXCreateFontA(device, 30, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font5);
	D3DXCreateFontA(device, 32, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font5);
	D3DXCreateFontA(device, 34, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &font5);

	scrw = ScrW;
	scrh = ScrH;

	return "";
}

/*
void m_d3d::Render(bool bReset)
{
	if (!device) return;
	if (!bReset && !canrender ) return;
	canrender = false;

	if (!bReset)
	{
		bFlushDraw = true;
		device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1, 0);
		device->BeginScene();

		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

		DoDraw();

		sprite->End();

		device->EndScene();
		device->Present(0, 0, 0, 0);
	}

	if (bReset && bFlushDraw)
	{
		device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1, 0);
		device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1, 0);
		device->Clear(0, 0, D3DCLEAR_STENCIL, 0, 1, 0);

		device->BeginScene();
		device->EndScene();
		device->Present(0, 0, 0, 0);
		bFlushDraw = false;
	}

}

*/