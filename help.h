#pragma once
#include "states.h"

class help : public states {
public:
	help(sf::RenderWindow* window, sf::RenderTarget* target);
	~help();
	void render();
	void update();
	int getNextState();
private:
	sf::Sprite BACK;
	void initButtons();
	int nextPage = -1;
	void checkClickBounds();
	void loadSound();
	sf::RenderTarget* target;
	sf::Window* window;
	sf::Sprite bg;
};