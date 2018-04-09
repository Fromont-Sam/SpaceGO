#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#pragma once
class Spaceship
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector3i guns;
	bool _doubleGun = false;
	int _speed, _health, _skin, _color;
	float _maxHealth;
	std::string getColor(int color) const;
	void initSpaceship(int type);
public:
	enum {
		SPACESHIP_SKIN_0, SPACESHIP_SKIN_1, SPACESHIP_SKIN_2, 
		SPACESHIP_SKIN_3, SPACESHIP_SKIN_4, SPACESHIP_SKIN_5,
		SPACESHIP_SKIN_6, SPACESHIP_SKIN_7, SPACESHIP_SKIN_8
	};
	enum {
		SPACESHIP_COLOR_RED, SPACESHIP_COLOR_YELLOW,
		SPACESHIP_COLOR_GREEN, SPACESHIP_COLOR_BLUE,
		SPACESHIP_COLOR_PURPLE, SPACESHIP_COLOR_PINK,
		SPACESHIP_COLOR_GREY, SPACESHIP_COLOR_ORANGE,
	};
	Spaceship();
	Spaceship(int skinType);
	Spaceship(int skinType, int colorType);
	~Spaceship();
	void setPosition(int x, int y);
	void move(int x, int y);
	void takeDamages();
	//Setter
	void setSkin(int skinType, int colorType);
	void addHealth();
	//Getters
	int getWidth() const;
	int getHeight() const;
	int getSkin() const;
	int getColor() const;
	int getX() const;
	int getY() const;
	int getHealth() const;
	float getMaxHealth() const;
	bool hasDoubleGun() const;
	sf::Vector3i getGuns() const;
	sf::Sprite getSprite() const;
};

