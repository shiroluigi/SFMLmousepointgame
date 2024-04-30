#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "projectile.h"
#include "Enemy.h"
#include "cstdlib"
#include "TextureLoader.h"

class states
{
public:
	states();
	virtual ~states();	
	virtual void render() = 0;
	virtual void update() = 0;
	virtual int getNextState();
};

