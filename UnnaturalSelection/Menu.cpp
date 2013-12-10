#include "Menu.h"

Menu::Menu(Game* game, Graphics* graphics) : 
	currentMenu(0), down(false), game(game), graphics(graphics), selectedIndex(0) {
		rendered.resize(menuNS::MAX_TEXT_ITEMS);
		int i = 0;
}

Menu::~Menu() {
//Delete all the menus!
	delete currentMenu;

	for (int i = 0; i < parents.size(); ++i) {
		parents.pop();
	}

//Delete all the text!
	for (int i = 0; i < rendered.size(); ++i) {
		delete rendered[i];
	}
}

void Menu::draw() {
	int spacing = (GAME_HEIGHT - menuNS::BOUND_BOTTOM - menuNS::BOUND_TOP) / (currentMenu->size() - 1);

//Draw the text
	for(int i = 0; i < currentMenu->size(); ++i) {
		rendered[i]->setFontColor((*currentMenu)[i].selected ? menuNS::FONT_COLOR_SELECTED : menuNS::FONT_COLOR_NORMAL);
		rendered[i]->print(
			(*currentMenu)[i].text,
			menuNS::BOUND_LEFT, 
			menuNS::BOUND_TOP + i * spacing,
			(*currentMenu)[i].align
		);
	}
}

void Menu::initialize(MenuCol mi) {
	items = mi;
	currentMenu = &items;
	int i = 0;

//Find the correct menu item to highlight
	for (auto it = currentMenu->begin(); it != currentMenu->end(); ++it, ++i) {
		if (it->defaultSelected) {
			selectedIndex = i;
			break;
		}
	}

//Initialize all of the text objects for the first level
	for(int i = 0; i < menuNS::MAX_TEXT_ITEMS; ++i) {
		rendered[i] = new TextDX();
		
		if(!rendered[i]->initialize(graphics, menuNS::FONT_SIZE_NORMAL, true, false, menuNS::FONT, GAME_WIDTH - menuNS::BOUND_RIGHT))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Menus are sad without text"));
	}

//Get the input
	input = game->getInput();
}

void Menu::update(float frametime) {
	if (!down) {
		(*currentMenu)[selectedIndex].selected = false;

	//Move down
		if (input->isKeyDown(menuNS::INPUT_DOWN)) {
			++selectedIndex;
			down = true;
		}        

	//Move up
		if (input->isKeyDown(menuNS::INPUT_UP)) {
			--selectedIndex;

			down = true;
		}

	//Select an item
		if (input->isKeyDown(menuNS::INPUT_SELECT)) {
		//Call the callback function, if there isn't a sub menu to drill into
			if ((*currentMenu)[selectedIndex].callback != 0) {
				(*currentMenu)[selectedIndex].callback(selectedIndex, (*currentMenu)[selectedIndex].text);
			}

		//Drill down into the sub menu
			if ((*currentMenu)[selectedIndex].subMenu.size() != 0) {
				parents.push(currentMenu);
				currentMenu = &((*currentMenu)[selectedIndex].subMenu);
				selectedIndex = 0;
				int i = 0;

			//Find the correct menu item to highlight
				for (auto it = currentMenu->begin(); it != currentMenu->end(); ++it, ++i) {
					if (it->defaultSelected) {
						selectedIndex = i;
						break;
					}
				}
			}

			down = true;
		}

	//Back out of a menu
		if (input->isKeyDown(menuNS::INPUT_LEFT) && parents.size() > 0) {
			currentMenu = parents.top();
			parents.pop();
			selectedIndex = 0;
			int i = 0;

		//Find the correct menu item to highlight
			for (auto it = currentMenu->begin(); it != currentMenu->end(); ++it, ++i) {
				if (it->defaultSelected) {
					selectedIndex = i;
					break;
				}
			}
		}
		
	//Check the bounds
		if (selectedIndex < 0) {
			selectedIndex = currentMenu->size() - 1;
		}

		if (selectedIndex >= currentMenu->size()) {
			selectedIndex = 0;
		}

		(*currentMenu)[selectedIndex].selected = true;
	} else {
		if (!input->isKeyDown(menuNS::INPUT_DOWN) && 
			!input->isKeyDown(menuNS::INPUT_UP) && 
			!input->isKeyDown(menuNS::INPUT_SELECT)) {
			down = false;
		}
	}
}