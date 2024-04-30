#include "projectile.h"

projectile::projectile(sf::Vector2f Ppos,std::string path, sf::RenderTarget* target)
{
	this->speed =  500;
	this->x = Ppos.x;
	this->y = Ppos.y;
	this->setSprite(path);
	this->window = target;
	
}

projectile::~projectile()
{
}

void projectile::render()
{
	this->window->draw(this->projectileSprite);
}

void projectile::update(float dt)
{
	this->go(this->projectileSprite.getRotation(),dt);
}

void projectile::setAngle(float angle)
{
	this->projectileSprite.setRotation(angle);
}

void projectile::go(float angle,float dt)
{
	this->projectileSprite.move(this->speed * sin(angle*3.1415/180) * dt, this->speed * ( - cos(angle * 3.1415 / 180) * dt));
}

sf::Vector2f projectile::getPos()
{
	return this->projectileSprite.getPosition();
}



void projectile::setSprite(std::string path)
{
	TextureLoader* tl = new TextureLoader();
	this->projectileSprite = tl->getSprite(path);
	this->projectileSprite.setOrigin(this->projectileSprite.getLocalBounds().width / 2, this->projectileSprite.getLocalBounds().height / 2);
	this->projectileSprite.setScale(sf::Vector2f(1, 1));
	this->projectileSprite.setPosition(sf::Vector2f(this->x, this->y));
}
