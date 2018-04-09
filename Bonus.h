#include "Obstacle.h"
#include "Laser.h"
#pragma once
class Bonus : public Obstacle
{
private :
	int _bonus;
public:
	static std::string getBonusSprite(int typeBonus);
	static int getColorLaser(int typeBonus);
	enum {
		BONUS_TYPE_GOD,
		BONUS_TYPE_DAMAGE,
		BONUS_TYPE_SPEED,
		BONUS_TYPE_HEAL,
		BONUS_TYPE_METEOR
	};
	Bonus(int minX, int minY, int y);
	~Bonus();
	//Getters
	int getBonus() const;
};

