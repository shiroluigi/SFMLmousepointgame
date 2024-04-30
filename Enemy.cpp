#include "Enemy.h"

Enemy::Enemy(int x, int y , std::string path, sf::RenderTarget* target)
{
	this->window = target;
	this->setSprite(path);
	this->enemySprite.setPosition(x, y);
	this->speed = 100;

}

Enemy::~Enemy()
{
}

void Enemy::render()
{
	this->window->draw(this->enemySprite);
}

void Enemy::update(float dt, sf::Vector2f playerPos, sf::Window &window)
{
	
	//Enemy will always know the player location and move to the location
	sf::Vector2f vectorToThePlayer = playerPos - this->enemySprite.getPosition();
	float magnitude = sqrt(vectorToThePlayer.x * vectorToThePlayer.x + vectorToThePlayer.y * vectorToThePlayer.y);
	//Normalize
	if (magnitude != 0)
	{
		vectorToThePlayer /= magnitude;
	}
	//Rotate move to the player
	this->enemySprite.move(vectorToThePlayer * (this->speed*dt));
	
}

void Enemy::setAngle(float angle)
{
}

void Enemy::go(float angle, float dt)
{
}

sf::Vector2f Enemy::getPos()
{
	return sf::Vector2f();
}

void Enemy::setSprite(std::string path)
{
	TextureLoader* tl = new TextureLoader();
	this->enemySprite = tl->getSprite(path);
	this->enemySprite.setPosition(this->window->getSize().x / 3, this->window->getSize().y / 3);
}
