#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <sstream>
#pragma once
class Meteor : public Obstacle
{
public:
	Meteor(int minX, int minY, int y);
	~Meteor();
	bool takeDamage();
};

