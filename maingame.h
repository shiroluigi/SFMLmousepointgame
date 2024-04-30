#pragma once
#include "states.h"

class maingame : public states
{
public:
	maingame(sf::RenderWindow* window);
	~maingame();
	void render();
	void update();
private:
	void initEntities();
	void updateDt();
	void makeProjectiles(std::vector<projectile*>& p, std::vector<float>& pa);
	void spawnEnemies(std::vector<Enemy*>& e);
	void playSound();
	void loadSound(sf::Sound* s, sf::SoundBuffer* sb, std::string path);
	void loadFont(std::string path);
	int getNextState();
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Sound bgm;
	sf::SoundBuffer bgmb;
	std::vector<float> projectleAngle;
	std::vector<projectile*> projectiles;
	std::vector<Enemy*> enemies;
	Player* p1;
	sf::RenderWindow* window = nullptr;
	float dt;
	sf::Clock dtClock;
	int countstart;
	int nextGameState = 1;
	sf::Text scoreText;
	sf::Font font;
	int score;
	sf::RenderTarget* target ;
	std::string text = "";
};

