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
	const int        BOUND_BOTTOM        = 100;
	const int        BOUND_LEFT          = 100;
	const int        BOUND_TOP           = 100;

	const char       FONT[]              = "Arial";
	const COLOR_ARGB FONT_COLOR_NORMAL   = D3DCOLOR_ARGB(255, 206, 206, 206); // Grey
	const COLOR_ARGB FONT_COLOR_SELECTED = D3DCOLOR_ARGB(255, 0, 0, 0);       // Black
	const int        FONT_SIZE_NORMAL    = 18;
	const int        FONT_SIZE_SELECTED  = 20;

	const UCHAR      INPUT_DOWN          = VK_DOWN;
	const UCHAR      INPUT_LEFT          = VK_LEFT;
	const UCHAR      INPUT_SELECT        = VK_RETURN;
	const UCHAR      INPUT_UP            = VK_UP;

	const int        MAX_TEXT_ITEMS      = 15;
}

typedef void(*FPtr)(); 

struct MenuItem {
public : 
	MenuItem() :
		callback(0), defaultSelected(false), selected(false), subMenu(0), text("") { }

	MenuItem(string text) : 
		callback(0), defaultSelected(false), selected(false), subMenu(NULL), text(text) { }

	MenuItem(string text, bool selected) : 
		callback(0), defaultSelected(selected), selected(selected), subMenu(NULL), text(text) { }

	MenuItem(string text, bool selected, FPtr callback) : 
		callback(callback), defaultSelected(selected), selected(selected), subMenu(NULL), text(text) { }

	MenuItem(string text, bool selected, vector<MenuItem> subMenu) : 
		callback(0), defaultSelected(selected), selected(selected), subMenu(subMenu), text(text) { }

	MenuItem(string text, bool selected, FPtr callback, vector<MenuItem> subMenu) : 
		callback(callback), defaultSelected(selected), selected(selected), subMenu(subMenu), text(text) { }

	~MenuItem() { }

    MenuItem(const MenuItem &r) {
        callback = r.callback;
		defaultSelected = r.defaultSelected;
		selected = r.selected;
		subMenu = r.subMenu;
		text = r.text;
    }
 
	MenuItem& operator=(const MenuItem &r) {
		callback = r.callback;
		defaultSelected = r.defaultSelected;
		selected = r.selected;
		subMenu = r.subMenu;
		text = r.text;
		
		return *this;
	}

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
	void update(float frametime);
};

#endif