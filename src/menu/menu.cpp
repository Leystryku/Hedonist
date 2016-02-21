#pragma once

#include "menu.h"
#include "menu_panels\elabel.h" // done
#include "menu_panels\epanel.h" // done
#include "menu_panels\eframe.h" // done
#include "menu_panels\ebutton.h" // done
#include "menu_panels\echeckbox.h" // done
#include "menu_panels\eslider.h" // done
#include "menu_panels\etextbox.h"
//todo: textbox, combobox

m_menu *menu;

element::element(element*dad)
{
	if (!menu)
		return;

	color.SetColor(39, 39, 39, 255);
	bordercolor.SetColor(255, 255, 255, 255);
	textcol.SetColor(255, 255, 255, 255);

	bordersize = 1;

	x, y, w, h = 1;
	parent = dad;

	name = "";

	visible = true;
	
	menu->elements[menu->num_elements++] = this;
	x_padding = 0;
	y_padding = 0;
	font = 0;

};

void element::Paint()
{
	int posx, posy;
	GetPos(posx, posy, true);

	d3d->DrawOutlinedRectangle(posx, posy, w, h, bordersize, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()), D3DCOLOR_RGBA(bordercolor.r(), bordercolor.g(), bordercolor.b(), bordercolor.a()));

	PaintOver();

}

void element::PaintOver()
{

}

void element::SetPos(int to_x, int to_y)
{

	x = to_x;
	y = to_y;
}

void element::SetPadding(int to_x, int to_y)
{
	x_padding = to_x;
	y_padding = to_y;
}

void element::GetPadding(int &f_x, int &f_y)
{
	f_x = x_padding;
	f_y = y_padding;
}

void element::SetSize(int new_w, int new_h)
{
	if (parent)
	{

		if (new_h > parent->h - 20)
			new_h = parent->h - 20;

	}

	w = new_w;
	h = new_h;


}

void element::GetPos(int &ix, int &iy, bool breal)
{

	if (breal&&parent)
	{
		int parentx, parenty;
		parent->GetPos(parentx, parenty, true);

		if (!parentx || !parenty)
			return GetPos(x, y, false);

		int truex = parentx + parent->x_padding + x;
		int truey = parenty + parent->y_padding + y;
		


		ix = truex;
		iy = truey;
		return;
	}

	ix = x;
	iy = y;



}

void element::GetSize(int &iw, int &ih)
{
	iw = w;
	ih = h;
}

void element::Center()
{

	int sizew=0, sizeh=0;
	GetSize(sizew, sizeh);

	if (parent)
	{
		int parentsizew, parentsizeh;
		parent->GetSize(parentsizew, parentsizeh);

		int x = (parentsizew / 2) - (sizew / 2);
		int y = (parentsizeh / 2) - (sizeh / 2);

		SetPos(x, y);

		return;
	}
	
	
	
	
	int x = (menu->ScrW / 2) - (sizew / 2);
	int y = (menu->ScrH / 2) - (sizeh / 2);

	SetPos(x, y);
}

void element::SetName(std::string newname)
{
	name = newname;
}

void element::SetFont(void* newfont)
{
	font = newfont;
}

void* element::GetFont()
{
	if (font)
		return font;

	return d3d->font2;
}

std::string element::GetName()
{
	return name;
}

void element::SetColor(Color to_col)
{
	color = to_col;
}

void element::SetBorderColor(Color to_col)
{
	bordercolor = to_col;
}

void element::SetBorderSize(int to_size)
{
	bordersize = to_size;
}

Color element::GetColor()
{
	return color;
}

Color element::GetBorderColor()
{
	return bordercolor;
}

Color element::GetTextColor()
{
	return textcol;
}

int element::GetBorderSize()
{
	return bordersize;
}

void element::SetVisible(bool visibility)
{
	visible = visibility;
}

bool element::GetVisible()
{

	if (parent && !parent->GetVisible())
		return false;

	return visible;
}

bool lastkeystates[1024];

bool element::GetToggleKeyState(int vk_key)
{
	short keystate = GetAsyncKeyState(vk_key);

	if ((keystate & 0x8000) && lastkeystates[vk_key])
		return false;

	if (keystate & 0x8000)
	{
		lastkeystates[vk_key] = true;
		return true;
	}

	lastkeystates[vk_key] = false;

	return false;
}

char curChar;
char element::GetCurChar()
{
	char ret = curChar;
	curChar = 0;
	return ret;
}

element *element::GetParent()
{
	return parent;
}
void element::SetParent(element *toparent)
{
	parent = toparent;
}


int element::MouseOver(int x1, int y1, int x2, int y2)
{

	

	int xx, yy;
	GetPos(xx, yy, true);

	if (GetParent())
		yy = yy;

	int xx2 = w;
	int yy2 = h;

	if (x1 && y1 && x2 && y2)
	{
		xx = x1;
		yy = y1;
		xx2 = x2;
		yy2 = y2;
	}



	if (menu->Cur.x > xx && menu->Cur.x < xx + xx2 && menu->Cur.y > yy && menu->Cur.y < yy + yy2)
	{

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			return 2;

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			return 3;

		return 1;
	}
	return 0;
}
void element::Think()
{

}

m_menu::m_menu()
{
	num_elements = 0;

	for (int i = 1; i < 666; i++)
		elements[i] = NULL;

	is_open = true;

	//settings
	bot_aim = false;


}


EFrame *MainFrame;
void m_menu::Initialize(int scrw, int scrh)
{
	ScrW = scrw;
	ScrH = scrh;

	is_open = true;

	MainFrame = new EFrame;
	MainFrame->SetSize(405, 350);
	MainFrame->Center();
	MainFrame->SetName("Hedonist");
		

}

void m_menu::Resize(int to_scrw, int to_scrh)
{
	menu->ScrW = to_scrw;
	menu->ScrH = to_scrh;
	MainFrame->Center();
}
