#include "Panel.h"
#include "Laser.h"
#include "Meteor.h"
#include "Star.h"
#include "Bonus.h"
#include "Ennemy.h"
#include "MyButton.h"
#include "Spaceship.h"
#pragma once
class Game : public Panel
{
private:
	bool _pause;
	int _ticks, _laserTicks, _typeBonus;
	float _pts, _speed, _timeBonus;
	MyButton btnMenu, btnQuit, _restart;
	Spaceship* spaceship;
	sf::Font font;
	sf::Text pts;
	sf::Texture pauseMenu, health, bonus, score, game_over, game_over_off, tbonus;
	sf::Sprite _pauseMenu, _health, _bonus, _score, _game_over, _tbonus;
	sf::RectangleShape rectHealth, rectBonus;
	std::vector<Laser> lasers;
	std::vector<Obstacle*> obstacles;
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Game(MyWindow* window);
	~Game();
	void init();
	void shoot();
	void pause();
	void restart();
	void manageShoots();
	void manageObstacles();
	//Listeners
	int keyPressed(int key);
	int keyPressedOnce(sf::Keyboard::Key key);
	void moveBackground();
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	int mouseMove(int x, int y);
	//Getters
	int getType() const;
};

