#include "Game.h"
#include <stdlib.h>
#include <time.h> 
#include <sstream>

Game::Game(MyWindow* window) : Panel(window)
{
	//Init buttons
	srand(time(NULL));
	//Pause
	if (!pauseMenu.loadFromFile("images/game/menu_pause.png")) {};
	if (!font.loadFromFile("fonts/masterbreaker.ttf")) {}
	if (!health.loadFromFile("images/game/health.png")) {};
	if (!bonus.loadFromFile("images/game/bonus.png")) {};
	if (!score.loadFromFile("images/game/score.png")) {};
	if (!game_over.loadFromFile("images/game/gameover.png")) {};
	if (!game_over_off.create(game_over.getSize().x, game_over.getSize().y)) {};

	_restart = MyButton("images/game/restart.png", "images/game/restart_s.png");
	_restart.changeTexture(false);
	btnMenu = MyButton("images/game/btn_menu.png", "images/game/btn_menu_s.png");
	btnQuit = MyButton("images/game/btn_quit.png", "images/game/btn_quit_s.png");

	_pauseMenu = sf::Sprite(pauseMenu);
	int skinType = getWindow()->getConfig()->getSelectedSpaceship();
	int colorType = getWindow()->getConfig()->getSelectedColor();
	spaceship = new Spaceship(skinType, colorType);

	//Init sound
	if (!buffer.loadFromFile("sounds/laser.wav")) {}
	sound.setBuffer(buffer);

	restart();
}

Game::~Game()
{
	for (size_t i = 0; i < obstacles.size(); i++) {
		delete obstacles[i];
	}
	delete spaceship;
}

void::Game::restart() {
	//Init variables
	_ticks = _laserTicks = _pts = 0;
	_typeBonus = -1;
	_timeBonus = 0;
	_speed = 12;
	_pause = false;
	lasers.clear();
	obstacles.clear();
	//Game
	pts = sf::Text("        0", font, 72);
	pts.setFillColor(sf::Color(249, 148, 7));

	rectHealth = sf::RectangleShape(sf::Vector2f(275, 51));
	rectHealth.setFillColor(sf::Color(195, 2, 2));
	rectHealth.setPosition(15, 60);
	rectBonus = sf::RectangleShape(sf::Vector2f(0, 120));
	rectBonus.setFillColor(sf::Color(249, 148, 7, 51));
	rectBonus.setPosition(17, 672);

	_bonus = sf::Sprite(bonus);
	_health = sf::Sprite(health);
	_game_over = sf::Sprite(game_over);
	_score = sf::Sprite(score);
	_tbonus = sf::Sprite(tbonus);

	//Spaceship
	int skinType = getWindow()->getConfig()->getSelectedSpaceship();
	int colorType = getWindow()->getConfig()->getSelectedColor();
	*spaceship = Spaceship(skinType, colorType);
	spaceship->setSkin(skinType, colorType);

	//Set position
	_pauseMenu.setPosition(590, 337);
	_health.setPosition(5, 11);
	_bonus.setPosition(4, 622);
	_score.setPosition(1270, 694);
	_game_over.setPosition(405, 190);
	pts.setPosition(1230, 710);
	_restart.setPosition(1343, 13);
	btnMenu.setPosition(629, 363);
	btnQuit.setPosition(647, 430);
	btnMenu.changeTexture(false);
	btnQuit.changeTexture(false);
	spaceship->setPosition(27, ((getWindow()->getSize().y - spaceship->getHeight()) / 2.));

	//Set todos
	btnMenu.setToDo(Panel::PANEL_MENU);
}

void Game::init()
{
	//Speed algo
	if (!_pause) {
		_pts += 0.1;
		_speed += 0.00032;
		std::stringstream ss;
		ss.width(8);
		ss << (int)_pts;
		pts.setString(ss.str());
	}
	if (_speed >= _timeBonus) {
		_typeBonus = -1;
	}
	//Skin settings changed
	if (spaceship->getSkin() != getWindow()->getConfig()->getSelectedSpaceship() || spaceship->getColor() != getWindow()->getConfig()->getSelectedColor()) {
		restart();
	}
	//Bonus changed
	if (!tbonus.loadFromFile(Bonus::getBonusSprite(_typeBonus))) {};
	_tbonus = sf::Sprite(tbonus);
	_tbonus.setPosition(17, 672);
	if (_typeBonus != -1) {
		rectBonus.setSize(sf::Vector2f(((_timeBonus - _speed) / 0.24 * 120), 120));
	}
	else {
		rectBonus.setSize(sf::Vector2f(0, 120));
	}
	//Settings
	_restart.setVolume(getWindow()->getConfig()->getVolume());
	btnMenu.setVolume(getWindow()->getConfig()->getVolume());
	btnQuit.setVolume(getWindow()->getConfig()->getVolume());
	sound.setVolume(getWindow()->getConfig()->getVolume());
	//Draw sprites
	getWindow()->clear();
	rectHealth.setSize(sf::Vector2f((275 * (spaceship->getHealth() / spaceship->getMaxHealth())), 51));
	getWindow()->draw(getBackground());
	manageShoots();
	manageObstacles();
	getWindow()->draw(spaceship->getSprite());
	getWindow()->draw(pts);
	getWindow()->draw(rectHealth); 
	getWindow()->draw(_health);
	getWindow()->draw(rectBonus);
	getWindow()->draw(_tbonus);
	getWindow()->draw(_bonus);
	getWindow()->draw(_score);
	getWindow()->draw(_restart.getSprite());
	//Paused
	if (_pause) {
		_ticks++;
		getWindow()->draw(_pauseMenu);
		getWindow()->draw(btnMenu.getSprite());
		getWindow()->draw(btnQuit.getSprite());
		if (spaceship->getHealth() <= 0) {
			getWindow()->draw(_game_over);
		}
		if (_ticks >= 30) {
			_game_over.setTexture(game_over);
		}
		if (_ticks >= 60) {
			_game_over.setTexture(game_over_off);
			_ticks = 0;
		}
	}
}

void Game::shoot()
{
	int lspeed;
	(_typeBonus == Bonus::BONUS_TYPE_SPEED) ? lspeed = 5 : lspeed = 10;
	if (_laserTicks > lspeed) {
		lasers.push_back(Laser((spaceship->getX()+spaceship->getGuns().x), (spaceship->getY()+spaceship->getGuns().y), Bonus::getColorLaser(_typeBonus)));
		if(spaceship->hasDoubleGun()) { 
			lasers.push_back(Laser((spaceship->getX() + spaceship->getGuns().x), (spaceship->getY() + spaceship->getGuns().z), Bonus::getColorLaser(_typeBonus)));
			_laserTicks = -lspeed;
		}
		else {
			_laserTicks = 0;
		}
		sound.play();
	}
}

void Game::pause()
{
	_pause = !_pause;
}

void Game::manageObstacles() {
	int chance;
	if (!_pause) {
		_ticks++;
		//Obstacles spawning
		if (_ticks > 40) {
			chance = rand() % 100;
			if (chance < 40) {
				obstacles.push_back(new Meteor(getWindow()->getSize().x + 300, getWindow()->getSize().y, rand()));
			}
			else if (chance < 82) {
				obstacles.push_back(new Ennemy(getWindow()->getSize().x + 300, getWindow()->getSize().y, rand()));
			}
			else if (chance < 94) {
				obstacles.push_back(new Star(getWindow()->getSize().x + 300, getWindow()->getSize().y, rand()));
			}
			else  {
				obstacles.push_back(new Bonus(getWindow()->getSize().x + 300, getWindow()->getSize().y, rand()));
			}
			_ticks = 0;
		}
		//Obstacles management
		for (size_t i = 0; i < obstacles.size(); i++)
		{
			//Out of bounds
			if (obstacles[i]->getSprite().getPosition().x < -obstacles[i]->getSprite().getGlobalBounds().width || obstacles[i]->getSprite().getPosition().y < -obstacles[i]->getSprite().getGlobalBounds().height)
			{
				obstacles.erase(obstacles.begin() + i);
			}
			//Collisions obstacles >< spaceship
			else if (obstacles[i]->getSprite().getGlobalBounds().intersects(spaceship->getSprite().getGlobalBounds()))
			{
				// Meteor OR Ennemy >< Spaceship
				if ((obstacles[i]->getType() == Obstacle::TYPE_METEOR) || (obstacles[i]->getType() == Obstacle::TYPE_ENNEMY)) {
					if(_typeBonus != Bonus::BONUS_TYPE_GOD) spaceship->takeDamages();
					//Game over
					if (spaceship->getHealth() <= 0) {
						getWindow()->getConfig()->addScore(_pts);
						getWindow()->getConfig()->addXp(_pts);
						pause();
					}
				}
				// Star >< Spaceship
				else if (obstacles[i]->getType() == Obstacle::TYPE_STAR) {
					getWindow()->getConfig()->addNbrStar();
				}
				// Bonus >< Spaceship
				else if (obstacles[i]->getType() == Obstacle::TYPE_BONUS) {
					if (obstacles[i]->getBonus() == Bonus::BONUS_TYPE_HEAL) {
						spaceship->addHealth();
					}
					else if (_typeBonus == -1 && _speed >= _timeBonus) {
						_typeBonus = obstacles[i]->getBonus();
						_timeBonus = _speed + 0.24;
					}
				}
				//Delete it 
				obstacles.erase(obstacles.begin() + i);
				break;
			}
		}
	}
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		if (!_pause) obstacles[i]->move(_speed);
		getWindow()->draw(obstacles[i]->getSprite());
	}
}

void Game::manageShoots()
{
	if (!_pause) {
		_laserTicks++;
		for (size_t i = 0; i < lasers.size(); i++)
		{
			//Out of bounds
			if (lasers[i].getSprite().getPosition().x < 0 || lasers[i].getSprite().getPosition().x > getWindow()->getSize().x
				|| lasers[i].getSprite().getPosition().y < 0 || lasers[i].getSprite().getPosition().y > getWindow()->getSize().y)
			{
				lasers.erase(lasers.begin() + i);
			}
			//Lasers management
			else
			{
				for (size_t k = 0; k < obstacles.size(); k++)
				{
					if (lasers[i].getSprite().getGlobalBounds().intersects(obstacles[k]->getSprite().getGlobalBounds()))
					{
						// Laser >< Metor OR Ennemy
						if ((obstacles[k]->getType() == Obstacle::TYPE_ENNEMY) || (_typeBonus == Bonus::BONUS_TYPE_METEOR && obstacles[k]->getType() == Obstacle::TYPE_METEOR)) {
							//Ennemy destroyed
							if (_typeBonus == Bonus::BONUS_TYPE_DAMAGE) {
								if (obstacles[k]->getType() == Obstacle::TYPE_ENNEMY) _pts += 150;
								obstacles.erase(obstacles.begin() + k);
							}
							else if (!obstacles[k]->takeDamage()) {
								if (obstacles[k]->getType() == Obstacle::TYPE_ENNEMY) _pts += 150;
								obstacles.erase(obstacles.begin() + k);
							}
						}
						lasers.erase(lasers.begin() + i);
						break;
					}
				}
			}
		}
	}
	for (size_t i = 0; i < lasers.size(); i++)
	{
		lasers[i].setSprite();
		if(!_pause) lasers[i].move();
		getWindow()->draw(lasers[i].getSprite());
	}
}

int Game::keyPressed(int key)
{
	switch (key) {
	case(sf::Keyboard::Key::Space): if(!_pause) shoot(); break;
	case(sf::Keyboard::Key::Z):
		if (!_pause && spaceship->getY()-10 > 0) 
			spaceship->move(0,-1);
		break;
	case(sf::Keyboard::Key::S):
		if (!_pause && (spaceship->getY() + spaceship->getHeight()+10) < getWindow()->getSize().y )
			spaceship->move(0, 1);
		break;
	case(sf::Keyboard::Key::Q):
		if (!_pause &&spaceship->getX()-10 > 0)
			spaceship->move(-1, 0);
		break;
	case(sf::Keyboard::Key::D):
		if (!_pause && (spaceship->getX() + spaceship->getWidth()+10) < (getWindow()->getSize().x) )
			spaceship->move(1, 0);
		break;
	case(sf::Keyboard::Key::R):
		restart();
		break;
	}
	return -1;
}

void Game::moveBackground()
{
	if (!_pause) {
		Panel::moveBackground();
	}
}
int Game::keyPressedOnce(sf::Keyboard::Key key)
{
	switch (key) {
	case(sf::Keyboard::Key::Escape): if (spaceship->getHealth() > 0) pause(); break;
	}
	return -1;
}


int Game::mouseClicked(int x, int y, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left) {
		if (btnMenu.isSelected(x, y)) {
			pause();
			restart();
			return btnMenu.toDo();
		}
		else if (_restart.isSelected(x, y)) {
			restart();
		}
		else if (btnQuit.isSelected(x, y)) {
			getWindow()->getConfig()->save();
			getWindow()->close();
		}
	}
	return -1;
}

int Game::mouseMove(int x, int y) {
	if (btnMenu.isSelected(x, y) && _pause) {
		btnMenu.changeTexture();
	}
	else if (btnQuit.isSelected(x, y) && _pause) {
		btnQuit.changeTexture();
	}
	else if (_restart.isSelected(x, y)) {
		_restart.changeTexture();
	}
	return -1;
}

int Game::getType() const
{
	return Panel::PANEL_GAME;
}


