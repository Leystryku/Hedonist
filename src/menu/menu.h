#pragma once

#include "../includes.h"
#include "../drawing/d3d.h"
#include "../drawing/color.h"

class element
{
private:

	bool visible;
	int x,y,w,h, x_padding, y_padding;
	element *parent;
	std::string name;
	
	Color color;
	Color bordercolor;
	Color textcol;
	int bordersize;
	void* font;

public:

	element(element* parent);
	element() : element(NULL) { }

	virtual void SetName(std::string);
	virtual void SetFont(void* newfont);
	virtual void SetPos(int x, int y);
	virtual void SetSize(int w, int h);
	virtual void SetVisible(bool visibility);
	virtual void GetSize(int &w, int &h);
	virtual void GetPos(int &x, int &y, bool breal);
	virtual void* GetFont();
	virtual bool GetVisible();
	virtual char GetCurChar();
	virtual bool GetToggleKeyState(int vk_key);
	virtual std::string GetName();
	virtual Color GetColor();
	virtual Color GetTextColor();
	virtual Color GetBorderColor();
	virtual int GetBorderSize();
	virtual void SetColor(Color tocolor);
	virtual void SetBorderColor(Color tocolor);
	virtual void SetBorderSize(int tosize);
	virtual void Center();
	virtual void SetParent(element* newparent);
	virtual void SetPadding(int x_padding, int y_padding);
	virtual void GetPadding(int &f_x, int &f_y);
	virtual element *GetParent();

	virtual void Paint();

	virtual void PaintOver();

	virtual int MouseOver(int x1,int y1, int x2, int y2);

	virtual void Think();

};



class m_menu
{
public:

	m_menu();

	void Initialize( int scrw, int scrh );
	void Resize(int to_scrw, int to_scrh);

	void *elements[666];
	int num_elements;
	int ScrW;
	int ScrH;
	
	bool is_open;

	POINT Cur;

	//settings

	bool bot_aim;


	std::string esp_customesp;
	std::string misc_text_spam_txt;


};

extern m_menu *menu;
