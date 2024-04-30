#include "Player.h"

Player::Player( std::string path,sf::RenderTarget* target)
{
	this->setSprite(path);
	this->speed = 100;
	this->rotateSpeed = 100;
	this->playerSprite.setPosition(target->getSize().x / 2, target->getSize().y / 2);
	this->window = target;
}

Player::~Player()
{
}

void Player::render()
{
	this->window->draw(this->playerSprite);
}

void Player::update(float dt, sf::Window &window)
{
	this->handleUserInputs(dt,window);
}

void Player::handleUserInputs(float dt, sf::Window &window)
{/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->playerSprite.move(sf::Vector2f(0, -this->speed * dt));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->playerSprite.move(sf::Vector2f(-this->speed * dt, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->playerSprite.move(sf::Vector2f(0, this->speed * dt));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->playerSprite.move(sf::Vector2f(this->speed * dt, 0));
	}
	//Rotate on click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		this->playerSprite.rotate(this->rotateSpeed * dt);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		this->playerSprite.rotate(-this->rotateSpeed * dt);
	}
	*/
	//Rotate to where the mouse is
	//get direction vector
	sf::Vector2f playerPos= this->playerSprite.getPosition();
	sf::Vector2i  mousePosLocal = sf::Mouse::getPosition(window);
	sf::Vector2f directionVector = sf::Vector2f(mousePosLocal.x - playerPos.x, mousePosLocal.y - playerPos.y);
	//get the magnitude of the direction vector
	float magnitude = sqrt((directionVector.x * directionVector.x) + (directionVector.y * directionVector.y));
	if (magnitude != 0)
	{
		directionVector /= magnitude;
	}
	//move the player to the direction of the mouse
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	this->playerSprite.move(directionVector *(this->speed * dt));
	//Angle Calculations
	float angle = atan2f(directionVector.x, directionVector.y) * 180/3.1415;
	angle += 180;
	this->playerSprite.setRotation(-angle);
}

sf::Vector2f Player::getPos()
{
	return this->playerSprite.getPosition();
}

float Player::getPlayerAngle()
{
	return this->playerSprite.getRotation();
}

sf::Vector2f Player::getPlayerPos()
{
	return this->playerSprite.getPosition();
}



void Player::setSprite(std::string path)
{
	TextureLoader* tl = new TextureLoader();
	this->playerSprite = tl->getSprite(path);
	this->playerSprite.setOrigin(this->playerSprite.getLocalBounds().width / 2 , this->playerSprite.getLocalBounds().height / 2);
	
}

