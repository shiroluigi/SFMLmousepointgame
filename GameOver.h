#pragma once
#include "states.h"

class GameOver : public states
{
public:
	GameOver(sf::RenderWindow* window,sf::RenderTarget* target);
	~GameOver();
	void render();
	void update();
	void initButtons();
	int getNextState();
private:
	sf::RenderWindow* window = nullptr;
	sf::RenderTarget* target = nullptr;
	int nextGameState = -1;
	sf::Text restartButton, exitButton, mainMenuButton;
	sf::Font font;
	void loadFont(std::string path);
};
