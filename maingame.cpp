#include "maingame.h"

maingame::maingame(sf::RenderWindow* window)
{
	this->window = window;
	this->target = this->window;
	this->initEntities();
	this->loadFont("Assets/Fonts/cutedino.ttf");
	this->bgm.setVolume(10);
	this->bgm.play();
}

maingame::~maingame()
{
}

void maingame::initEntities()
{
	this->score = 0;
	this->p1 = new Player("Assets/player1.png", this->window);
	this->loadSound(&this->sound,&this->buffer,"Assets/Sounds/hit.wav");
	this->loadSound(&this->bgm,&this->bgmb,"Assets/Sounds/gamebgm1.mp3");
}


void maingame::render()
{
	text = "Score : " + std::to_string(this->score);
	this->scoreText.setString(text);
	this->target->draw(this->scoreText);
	this->p1->render();
	for (int i = 0; i < this->projectiles.size(); i++)
	{
		this->projectiles[i]->render();
	}
	for (auto& e : enemies)
	{
		e->render();
	}
}

void maingame::update()
{
	//check escape
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->nextGameState = GAMEOVER;
	}
	if (!(this->bgm.getStatus() == sf::Sound::Status::Playing))
		this->bgm.play();
	this->spawnEnemies(this->enemies);
	this->makeProjectiles(this->projectiles, this->projectleAngle);
	for (int i = 0; i < this->projectiles.size(); i++)
	{
		if (this->projectiles[i]->getPos().x > this->window->getSize().x && this->projectiles[i]->getPos().y > this->window->getSize().y
			|| this->projectiles[i]->getPos().x < 0 && this->projectiles[i]->getPos().y<0
			|| this->projectiles[i]->getPos().x >  this->window->getSize().x
			|| this->projectiles[i]->getPos().y > this->window->getSize().y)
		{
			auto* ptr = this->projectiles[i];
			this->projectiles.erase(this->projectiles.begin() + i);
			delete ptr;
			continue;
		}
		this->projectiles[i]->update(this->dt);
	}
	this->p1->update(this->dt, *this->window);
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->update(dt, this->p1->getPlayerPos(), *this->window);
	}
	//check collision for player and enemies
	for(auto* q : enemies)
	{
		if (this->p1->getSprite()->getGlobalBounds().intersects(q->enemySprite.getGlobalBounds()))
		{
			this->nextGameState = GAMEOVER;
			return;
		}
	}
	//check collision for projectiles and enemies
	for (auto* p : projectiles)
	{
		for (auto* q : enemies)
		{
			if (p->projectileSprite.getGlobalBounds().intersects(q->enemySprite.getGlobalBounds()))
			{
				this->score++;
				this->playSound();
				auto pend = std::remove(projectiles.begin(), projectiles.end(), p);
				projectiles.erase(pend, projectiles.end());
				auto eend = std::remove(enemies.begin(), enemies.end(), q);
				enemies.erase(eend, enemies.end());
				delete p;
				delete q;
			}
		}
	}
	this->updateDt();
}
void maingame::playSound()
{
	this->sound.play();
	this->sound.setVolume(5);
}
void maingame::loadSound(sf::Sound* s,sf::SoundBuffer* sb,std::string path)
{
	if (!sb->loadFromFile(path))
	{
		std::cout << "SOund error ";
	}
	s->setBuffer(*sb);
}

void maingame::loadFont(std::string path)
{
	this->font.loadFromFile(path);
	this->font.setSmooth(true);
	this->scoreText.setFont(this->font);
	this->scoreText.setString("score");
	this->scoreText.setCharacterSize(50);
	this->scoreText.setFillColor(sf::Color::Black);
}

int maingame::getNextState()
{
	return this->nextGameState;
}

void maingame::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void maingame::makeProjectiles(std::vector<projectile*>& p, std::vector<float>& pa)
{
	countstart++;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && countstart > 100)
	{
		this->countstart = 0;
		//std::cout << "Making Projectile" << std::endl;
		projectile* pro = new projectile(this->p1->getPos(), "Assets/bullet.png", this->window);
		pro->setAngle(this->p1->getPlayerAngle());
		p.push_back(std::move(pro));
		pa.push_back(this->p1->getPlayerAngle());
	}
}

void maingame::spawnEnemies(std::vector<Enemy*>& e)
{
	if (e.size() < 8)
	{
		//enemies cannot spawn on top of player
		int socialDistancing = 300;
		sf::Vector2f playerPos = p1->getSprite()->getPosition();
		Enemy* en = new Enemy(rand() % this->window->getSize().x, rand() % this->window->getSize().y, "Assets/enemy.png", this->window);
		sf::Vector2f enemyPos = en->enemySprite.getPosition();
		//check distance on both axes
		if (std::abs(enemyPos.x - playerPos.x) < socialDistancing &&
			std::abs(enemyPos.y - playerPos.y) < socialDistancing)
		{
			delete en;
			return;
		}
		e.push_back(std::move(en));
	}
}
