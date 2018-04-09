#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#pragma once
class Ennemy : public Obstacle
{
private:
	bool _direction;
public:
	Ennemy(int minX, int minY, int y);
	~Ennemy();
	void move(float speed);
	bool takeDamage();
};

