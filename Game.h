#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "maingame.h"
#include "mainmenu.h"
#include "help.h"
#include "states.h"
#include "GameOver.h"

class Game
{
public:
	Game(int x, int y, std::string title);
	~Game();

private:
	void initwindow(int x, int y, std::string title);
	void initEntities();
	void initStates();
	void render();
	void update();
	states* states_vector[4];
	int stateNumber;
	int prevstate = 0;
	int currentState = 0;
	sf::RenderWindow* window = nullptr;
	sf::Image icon;
	void clearAllStates();
public: 
	bool isRunning = false;
	void run();
	void pollevents();
	sf::Sprite bg;
};

