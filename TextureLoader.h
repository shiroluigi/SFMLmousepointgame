#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();
	sf::Sprite getSprite(std::string path);
private:
	void LoadTexture(std::string path);
	sf::Texture texture;
	sf::Sprite sprite;
};

