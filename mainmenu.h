#pragma once
#include "states.h"

class mainmenu : public states
{
public:
	mainmenu(sf::Window* window,sf::RenderTarget* target);
	~mainmenu();
	void render();
	void update();
	int nextWindow();
	int getNextState();
private:
	sf::Sprite START_GAME, QUIT, HELP;
	void initButtons();
	int nextPage;
	void checkClickBounds();
	void loadSound();
	sf::RenderTarget* target;
	sf::Window* window;
	sf::Sound bgm;
	sf::SoundBuffer sb;
	sf::Sprite bg;
};

