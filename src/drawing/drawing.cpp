#include "drawing.h"
#include "d3d.h"
#include "../menu/menu.h"

INT Fps = 0;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;
CHAR FrameRate[50] = "";
#include "../main.h"

void Drawing::DoDraw()
{
	d3d->DrawTextW("hello world", 100, 100, D3DCOLOR_RGBA(255, 0, 0, 255), d3d->font4);

	if (!menu)
		return;
	
	GetCursorPos(&menu->Cur);

	if (ScreenToClient(Main->window_handle, &menu->Cur))
	{
		//p.x and p.y are now relative to hwnd's client area
	}

	for (int i = 0; i < menu->num_elements; i++)
	{
		element *e = (element*)menu->elements[i];

		if (!e)
			continue;

		e->Think();

	}

	for (int i = 0; i < menu->num_elements; i++)
	{
		element *e = (element*)menu->elements[i];

		if (!e)
			continue;

		if (e->GetVisible())
			e->Paint();

	}

	if (!menu->is_open)
		return;

	CurrentTickCount = clock() * 0.001f;
	Fps++;

	if ((CurrentTickCount - LastTickCount) > 1.0f)
	{
		LastTickCount = CurrentTickCount;
		sprintf_s(FrameRate, "[ FPS: %d ]", Fps);
		Fps = 0;
	}

	d3d->DrawText(FrameRate, 10, 50, D3DCOLOR_RGBA(255, 255, 255, 255), d3d->font2);

	DWORD color = D3DCOLOR_RGBA(122, 139, 139, 255);
	int x = menu->Cur.x;
	int y = menu->Cur.y;


	d3d->DrawRectangle(x, y, 11, 1, color);
	d3d->DrawRectangle(x + 1, y + 1, 9, 1, color);
	d3d->DrawRectangle(x + 2, y + 2, 7, 1, color);
	d3d->DrawRectangle(x + 3, y + 3, 7, 1, color);
	d3d->DrawRectangle(x + 4, y + 4, 8, 1, color);
	d3d->DrawRectangle(x + 5, y + 5, 3, 1, color);
	d3d->DrawRectangle(x + 6, y + 6, 2, 1, color);

	//draw end

	
}

void Drawing::DoThink( bool FlushScreen )
{
	if (!d3d->device)  return;

	if (FlushScreen)
	{
		d3d->device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1, 0);
		d3d->device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1, 0);
		d3d->device->Clear(0, 0, D3DCLEAR_STENCIL, 0, 1, 0);

		d3d->device->BeginScene();
		d3d->device->EndScene();
		d3d->device->Present(0, 0, 0, 0);
		return;
	}

	d3d->device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3d->device->BeginScene();

	d3d->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	DoDraw();

	d3d->device->EndScene();
	d3d->device->Present(0, 0, 0, 0);

	d3d->sprite->End();

}
