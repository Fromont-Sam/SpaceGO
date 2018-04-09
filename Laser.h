#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#pragma once
class Laser
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int _type;
public:
	enum {
		LASER_TYPE_BLUE,
		LASER_TYPE_RED,
		LASER_TYPE_GREEN,
		LASER_TYPE_YELLOW
	};
	Laser(int x, int y);
	Laser(int x, int y, int type);
	~Laser();
	void move();
	void setSprite();
	int getType() const;
	sf::Sprite getSprite() const;
};

