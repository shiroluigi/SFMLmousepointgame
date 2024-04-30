#pragma once
#include "TextureLoader.h"
#include <SFML/Audio.hpp>

class projectile
{
public:
	projectile(sf::Vector2f Ppos,std::string path, sf::RenderTarget* target);
	~projectile();
	void render();
	void update(float dt);
	void setAngle(float angle);
	void go(float angle,float dt);
	sf::Vector2f getPos();
	sf::Sprite projectileSprite;
	
private:
	void setSprite(std::string path);
	sf::RenderTarget* window;
	int x, y;
	sf::Vector2i vel;
	int speed;

};

