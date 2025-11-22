#include "Game.h"

Game::Game(int x, int y, std::string title)
{
	this->initwindow(x, y, title);
	this->initEntities();
	this->initStates();
}

Game::~Game()
{
	
}

void Game::initwindow(int x, int y, std::string title)
{
	this->window = new sf::RenderWindow(sf::VideoMode(x, y), title ,sf::Style::Close);
	if (!window)
	{
		std::cout << "Error" << std::endl;
	}
	isRunning = true;
}

void Game::initEntities()
{
	TextureLoader *tl = new TextureLoader();
	this->bg = tl->getSprite("Assets/goku.jpg");
	this->bg.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->bg.setOrigin(this->bg.getLocalBounds().width / 2, this->bg.getLocalBounds().height / 2);
	this->bg.setScale(this->window->getSize().x / this->bg.getLocalBounds().width, this->window->getSize().y / this->bg.getLocalBounds().height);
	/*
	this->g = new maingame(this->window);
	this->mm = new mainmenu(this->window, this->window);
	this->s = new mainmenu(this->window, this->window);
	*/
}

void Game::initStates()
{
	//state 0 ->menu
	states_vector[0] = (std::move(new mainmenu(this->window, this->window)));
	//state 1 ->game
	//states_vector.push_back(std::move(new maingame(this->window)));
	//state 2 -> help
	//states_vector.push_back(std::move(new help(this->window, this->window)));
	this->stateNumber = 0;
}

void Game::pollevents()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			this->isRunning = false;
	}
}

void Game::render()
{
	this->window->clear(sf::Color::White);
	this->window->draw(this->bg);
	this->states_vector[this->stateNumber]->render();
	this->window->display();
}

void Game::update()
{
	this->states_vector[this->stateNumber]->update();
	if (this->states_vector[this->stateNumber]->getNextState() == 1)
	{
		this->stateNumber = 1;
		states* s = this->states_vector[0];
		states_vector[0] = nullptr;
		delete s;
		states_vector[1] = (std::move(new maingame(this->window)));
	}
	else if (this->states_vector[this->stateNumber]->getNextState()  ==  2)
	{
		this->stateNumber = 2;
		states* s = this->states_vector[0];
		states_vector[0] = nullptr;
		delete s;
		states_vector[2] = (std::move(new help(this->window,this->window)));
	}
	else if (this->states_vector[this->stateNumber]->getNextState() == 0)
	{
		this->stateNumber = 0;
		for(int i=1;i<3;i++)
		{
			states* s = this->states_vector[i];
			states_vector[i] = nullptr;
			delete s;
		}
		states_vector[0] = (std::move(new mainmenu(this->window, this->window)));
	}
	else if (this->states_vector[this->stateNumber]->getNextState() == EXIT)
	{
		this->stateNumber = EXIT;
		for (int i = 1;i < 3;i++)
		{
			states* s = this->states_vector[i];
			states_vector[i] = nullptr;
			delete s;
		}
		this->isRunning = false;
	}
}
void Game::run()
{
	this->pollevents();
	this->render();
	this->update();
}