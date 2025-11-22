#include "help.h"

help::help(sf::RenderWindow* window, sf::RenderTarget* target)
{
	this->window = window;
	this->target = target;
	this->initButtons();
}
help::~help()
{
}
void help::render()
{
	this->checkClickBounds();
	this->target->draw(this->bg);
	this->target->draw(this->BACK);
}
void help::update()
{
}
int help::getNextState()
{
	return this->nextPage;
}
void help::initButtons()
{
	TextureLoader* tl = new TextureLoader();
	this->BACK = std::move(tl->getSprite("Assets/back.png"));
	this->BACK.setOrigin(this->BACK.getLocalBounds().getSize().x / 2, this->BACK.getLocalBounds().getSize().y / 2);
	this->BACK.setScale(0.5, 0.5);
	this->BACK.setPosition(50, 50);
}
void help::checkClickBounds()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		sf::FloatRect backBounds = this->BACK.getGlobalBounds();
		if (backBounds.contains(static_cast<sf::Vector2f>(mousePos)))
		{
			this->nextPage = 0;
		}
	}
}
