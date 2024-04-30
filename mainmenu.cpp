#include "mainmenu.h"

mainmenu::mainmenu(sf::Window* window,sf::RenderTarget* target)
{
	this->window = window;
	this->target = target;
	this->initButtons();
	this->loadSound();
	this->bgm.play();
}

mainmenu::~mainmenu()
{
}

void mainmenu::render()
{
	this->checkClickBounds();
	this->target->draw(this->bg);
	this->target->draw(this->START_GAME);
	this->target->draw(this->HELP);
	this->target->draw(this->QUIT);
}

void mainmenu::update()
{
}

int mainmenu::nextWindow()
{
	return nextPage;
}

int mainmenu::getNextState()
{
	return this->nextPage;
}

void mainmenu::initButtons()
{
	TextureLoader* tl = new TextureLoader();
	this->START_GAME = std::move(tl->getSprite("Assets/start.png"));
	tl = new TextureLoader();
	this->HELP = tl->getSprite("Assets/help.png");
	tl = new TextureLoader();
	this->QUIT = tl->getSprite("Assets/quit.png");
	tl = new TextureLoader();
	this->bg = tl->getSprite("Assets/menubg.jpg");
	this->bg.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->bg.setOrigin(this->bg.getLocalBounds().width / 2, this->bg.getLocalBounds().height / 2);
	this->bg.setScale(this->window->getSize().x / this->bg.getLocalBounds().width, this->window->getSize().y / this->bg.getLocalBounds().height);

	this->START_GAME.setOrigin(this->START_GAME.getLocalBounds().getSize().x /  2, this->START_GAME.getLocalBounds().getSize().y/ 2);
	this->HELP.setOrigin(this->HELP.getLocalBounds().getSize().x /  2, this->HELP.getLocalBounds().getSize().y/ 2);
	this->QUIT.setOrigin(this->QUIT.getLocalBounds().getSize().x /  2, this->QUIT.getLocalBounds().getSize().y/ 2);
	this->HELP.setScale(0.5, 0.5);
	this->QUIT.setScale(0.5, 0.5);
	this->START_GAME.setScale(0.5, 0.5);
	this->START_GAME.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 - 300);
	this->HELP.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 );
	this->QUIT.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 + 300);
}

void mainmenu::checkClickBounds()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouseposonclick =(sf::Vector2f) sf::Mouse::getPosition(*this->window);
		if (this->START_GAME.getGlobalBounds().contains(mouseposonclick))
		{
			this->nextPage = 1;
		}
		else if (this->QUIT.getGlobalBounds().contains(mouseposonclick))
		{
			this->nextPage = 999;
		}
		else if (this->HELP.getGlobalBounds().contains(mouseposonclick))
		{
			this->nextPage = 2;
		}
	}
	
}

void mainmenu::loadSound()
{
	if (!this->sb.loadFromFile("Assets/Sounds/mainmenu_music.mp3"))
	{
		std::cout << "Error";
	}
	
	this->bgm.setBuffer(sb);
}
