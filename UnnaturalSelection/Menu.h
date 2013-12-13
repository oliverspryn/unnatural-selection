#ifndef MENU_H
#define MENU_H

#include <stack>
#include <string>
#include <vector>

#include "game.h"
#include "graphics.h"
#include "textDX.h"

using std::stack;
using std::string;
using std::vector;

namespace menuNS {
	const int        ALIGN_CENTER        = DT_CENTER;
	const int        ALIGN_LEFT          = DT_LEFT;
	const int        ALIGN_RIGHT         = DT_RIGHT;

	const int        BOUND_BOTTOM        = 100;
	const int        BOUND_LEFT          = 100;
	const int        BOUND_RIGHT         = 100;
	const int        BOUND_TOP           = 200;

	const char       FONT[]              = "Arial";
	const COLOR_ARGB FONT_COLOR_DISABLED = D3DCOLOR_ARGB(255, 100, 100, 100); // Greyish
	const COLOR_ARGB FONT_COLOR_NORMAL   = D3DCOLOR_ARGB(255, 255, 255, 0);   // Yellow
	const COLOR_ARGB FONT_COLOR_SELECTED = D3DCOLOR_ARGB(255, 0, 255, 0);     // Green
	const int        FONT_SIZE_DISABLED  = 18;
	const int        FONT_SIZE_NORMAL    = 18;
	const int        FONT_SIZE_SELECTED  = 20;

	const UCHAR      INPUT_DOWN          = VK_DOWN;
	const UCHAR      INPUT_LEFT          = VK_LEFT;
	const UCHAR      INPUT_SELECT        = VK_RETURN;
	const UCHAR      INPUT_UP            = VK_UP;

	const int        MAX_TEXT_ITEMS      = 15;
}

typedef void(*FPtr)(int, string); 

struct MenuItem {
public : 
	MenuItem() : 
		align(menuNS::ALIGN_LEFT), callback(0), defaultSelected(false), selected(false), subMenu(0), text("") { }

	MenuItem(string text) : 
		align(menuNS::ALIGN_LEFT), callback(0), defaultSelected(false), selected(false), subMenu(NULL), text(text) { }

	MenuItem(string text, int align) : 
		align(align), callback(0), defaultSelected(false), selected(false), subMenu(NULL), text(text) { }

	MenuItem(string text, bool selected) : 
		align(menuNS::ALIGN_LEFT), callback(0), defaultSelected(selected), selected(selected), subMenu(NULL), text(text) { }

	MenuItem(string text, int align, bool selected) : 
		align(align), callback(0), defaultSelected(selected), selected(selected), subMenu(NULL), text(text) { }

	MenuItem(string text, int align, vector<MenuItem> subMenu) : 
		align(align), callback(0), defaultSelected(false), selected(false), subMenu(subMenu), text(text) { }

	MenuItem(string text, int align, FPtr callback) : 
		align(align), callback(callback), defaultSelected(false), selected(false), subMenu(NULL), text(text) { }

	MenuItem(string text, bool selected, vector<MenuItem> subMenu) : 
		align(menuNS::ALIGN_LEFT), callback(0), defaultSelected(selected), selected(selected), subMenu(subMenu), text(text) { }

	MenuItem(string text, bool selected, FPtr callback) : 
		align(menuNS::ALIGN_LEFT), callback(callback), defaultSelected(selected), selected(selected), subMenu(NULL), text(text) { }

	MenuItem(string text, int align, bool selected, FPtr callback) : 
		align(align), callback(callback), defaultSelected(selected), selected(selected), subMenu(NULL), text(text) { }

	MenuItem(string text, int align, bool selected, vector<MenuItem> subMenu) : 
		align(align), callback(0), defaultSelected(selected), selected(selected), subMenu(subMenu), text(text) { }

	MenuItem(string text, int align, FPtr callback, vector<MenuItem> subMenu) : 
		align(align), callback(callback), defaultSelected(false), selected(false), subMenu(subMenu), text(text) { }

	MenuItem(string text, bool selected, FPtr callback, vector<MenuItem> subMenu) : 
		align(menuNS::ALIGN_LEFT), callback(callback), defaultSelected(selected), selected(selected), subMenu(subMenu), text(text) { }

	MenuItem(string text, int align, bool selected, FPtr callback, vector<MenuItem> subMenu) : 
		align(align), callback(callback), defaultSelected(selected), selected(selected), subMenu(subMenu), text(text) { }

	~MenuItem() { }

    MenuItem(const MenuItem &r) {
		align = r.align;
        callback = r.callback;
		defaultSelected = r.defaultSelected;
		selected = r.selected;
		subMenu = r.subMenu;
		text = r.text;
    }
 
	MenuItem& operator=(const MenuItem &r) {
		align = r.align;
		callback = r.callback;
		defaultSelected = r.defaultSelected;
		selected = r.selected;
		subMenu = r.subMenu;
		text = r.text;
		
		return *this;
	}

	int               align;
	FPtr              callback;
	bool              defaultSelected;
	vector<MenuItem>* parentMenu;
	bool              selected;
	vector<MenuItem>  subMenu;
	string            text;
};

typedef vector<MenuItem> MenuCol;

class Menu {
private : 
	MenuCol*        currentMenu;
	bool            down;
	int             selectedIndex;
	stack<MenuCol*> parents;

	int             bottom;
	int             left;
	int             right;
	int             top;

protected : 
	Game*           game;
	Graphics*       graphics;
	Input*          input;
	MenuCol         items;
	vector<TextDX*> rendered;

public : 
	Menu(Game* game, Graphics* graphics);
	~Menu();

	void draw();
	void initialize(MenuCol mi);
	void setParams(int top, int right, int bottom, int left);
	void update(float frametime);
};

#endif