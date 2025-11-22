#pragma once
#include "TextureLoader.h"

struct Player
{
	Player(std::string path,sf::RenderTarget* target);
	~Player();
	void render();
	void update(float dt, sf::Window  &window);
	void handleUserInputs(float dt,sf::Window &window);
	sf::Vector2f getPos();
	float getPlayerAngle();
	sf::Vector2f getPlayerPos();
	sf::Sprite* getSprite();
private:
	void setSprite(std::string path);
	sf::Sprite playerSprite;
	sf::RenderTarget* window;
	int speed;
	int rotateSpeed;
};

