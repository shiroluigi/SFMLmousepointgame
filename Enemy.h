#pragma once
#include "TextureLoader.h"
class Enemy
{
public:
	Enemy(int x, int y , std::string path, sf::RenderTarget* target);
	~Enemy();
	void render();
	void update(float dt, sf::Vector2f playerPos, sf::Window &window);
	void setAngle(float angle);
	void go(float angle, float dt);
	sf::Vector2f getPos();
	sf::Sprite enemySprite;
	int speed;
private:
	void setSprite(std::string path);
	sf::RenderTarget* window;
	
};

