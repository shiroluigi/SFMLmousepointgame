#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "maingame.h"
#include "mainmenu.h"
#include "states.h"
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
	std::vector<states*> states_vector;
	int stateNumber;
	int prevstate = 0;
	sf::RenderWindow* window = nullptr;
	bool s1;
	bool s0;
public: 
	bool isRunning = false;
	void run();
	void pollevents();
	sf::Sprite bg;
};

