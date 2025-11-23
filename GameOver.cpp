#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow* window,sf::RenderTarget* target)
{
	this->target = target;
	this->window = window;
	this->initButtons();
}
GameOver::~GameOver()
{
}
void GameOver::render()
{
	this->target->draw(this->restartButton);
	this->target->draw(this->exitButton);
	this->target->draw(this->mainMenuButton);
}
void GameOver::update()
{
	//check for mouse click on buttons
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		sf::FloatRect restartBounds = this->restartButton.getGlobalBounds();
		sf::FloatRect exitBounds = this->exitButton.getGlobalBounds();
		sf::FloatRect mainMenuBounds = this->mainMenuButton.getGlobalBounds();
		if (restartBounds.contains(static_cast<sf::Vector2f>(mousePos)))
		{
			this->nextGameState = MAINGAME;
		}
		else if (mainMenuBounds.contains(static_cast<sf::Vector2f>(mousePos)))
		{
			this->nextGameState = MAINMENU;
		}
		else if (exitBounds.contains(static_cast<sf::Vector2f>(mousePos)))
		{
			this->nextGameState = EXIT;
		}
	}
}
void GameOver::initButtons()
{
	loadFont("Assets/Fonts/cutedino.ttf");
}
void GameOver::loadFont(std::string path)
{
	this->font.loadFromFile(path);
	this->font.setSmooth(true);

	this->restartButton.setFont(this->font);
	this->restartButton.setString("Restart");
	this->restartButton.setCharacterSize(50);
	this->restartButton.setFillColor(sf::Color::Black);
	this->exitButton.setFont(this->font);
	this->exitButton.setString("Exit");
	this->exitButton.setCharacterSize(50);
	this->exitButton.setFillColor(sf::Color::Black);
	this->mainMenuButton.setFont(this->font);
	this->mainMenuButton.setString("Main Menu");
	this->mainMenuButton.setCharacterSize(50);
	this->mainMenuButton.setFillColor(sf::Color::Black);

	this->restartButton.setOrigin(this->restartButton.getLocalBounds().getSize().x / 2, this->restartButton.getLocalBounds().getSize().y / 2);
	this->mainMenuButton.setOrigin(this->mainMenuButton.getLocalBounds().getSize().x / 2, this->mainMenuButton.getLocalBounds().getSize().y / 2);
	this->exitButton.setOrigin(this->exitButton.getLocalBounds().getSize().x / 2, this->exitButton.getLocalBounds().getSize().y / 2);

	this->restartButton.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 - 100);
	this->mainMenuButton.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->exitButton.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 + 100);

	this->restartButton.setScale(1, 1);
	this->mainMenuButton.setScale(1, 1);
	this->exitButton.setScale(1, 1);
}
int GameOver::getNextState()
{
	return this->nextGameState;
}
