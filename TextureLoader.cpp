#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

sf::Sprite TextureLoader::getSprite(std::string path)
{
	this->LoadTexture(path);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(sf::Vector2f(1.f, 1.f));
	this->sprite.setScale(sf::Vector2f(2.f, 2.f));
	return this->sprite;
}

void TextureLoader::LoadTexture(std::string path)
{
	if (!this->texture.loadFromFile(path))
	{
		std::cout << "Error texture" << std::endl;
	}
	//this->texture.setSmooth(true);
}

