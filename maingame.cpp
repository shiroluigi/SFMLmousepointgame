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
	this->p1 = new Player("Assets/player.png", this->window);
	this->loadSound(&this->sound,&this->buffer,"Assets/Sounds/hit.wav");
	this->loadSound(&this->bgm,&this->bgmb,"Assets/Sounds/gametheme.mp3");
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
		this->nextGameState = 9999;
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
			//std::cout << "Object is removed" << this->projectiles[i]->getPos().x << " " << this->projectiles[i]->getPos().y;
			auto* ptr = this->projectiles[i];
			//std::cout << "before" << this->projectiles.size() << std::endl;
			this->projectiles.erase(this->projectiles.begin() + i);
			//std::cout << "after" << this->projectiles.size() << std::endl;
			delete ptr;
			continue;
		}
		//std::cout << this->dt << std::endl;
		this->projectiles[i]->update(this->dt);
	}
	this->p1->update(this->dt, *this->window);
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->update(dt, this->p1->getPlayerPos(), *this->window);
	}
	//this->e1->update(this->dt,this->p1->getPlayerPos(), *this->window);
	//check collision
	for (auto* p : projectiles)
	{
		for (auto* q : enemies)
		{
			if (p->projectileSprite.getGlobalBounds().intersects(q->enemySprite.getGlobalBounds()))
			{
				this->score++;
				//std::cout << sizeof(this->projectiles) << "< projectiles" << std::endl;
				//std::cout << sizeof(this->enemies) << "< enemies" << std::endl;
				this->playSound();
				auto pend = std::remove(projectiles.begin(), projectiles.end(), p);
				projectiles.erase(pend, projectiles.end());
				auto eend = std::remove(enemies.begin(), enemies.end(), q);
				enemies.erase(eend, enemies.end());
				delete p;
				delete q;
				//std::cout << p << std::endl;
				//std::cout << sizeof(this->projectiles) << "< projectiles" << std::endl;
				//std::cout << sizeof(this->enemies) << "< enemies" << std::endl;
			}
		}
	}
	this->updateDt();
}
void maingame::playSound()
{
	this->sound.play();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && countstart > 100)
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
		Enemy* en = new Enemy(rand() % this->window->getSize().x, rand() % this->window->getSize().y, "Assets/enemy.png", this->window);
		e.push_back(std::move(en));
		//std::cout << sizeof(en) << std::endl;
	}
}
