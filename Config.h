#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#pragma warning(disable:4996)
#pragma once
class Config
{
private:
	int _volume, _lvl, _xp, _nbrStar, _sSpaceship, _sColor;
	bool _noReset, _music, _vsync;
	std::vector<bool> spaceships;
	std::vector<bool> colors;
	std::vector<int> scores;
	std::vector<std::string> dates;
public:
	Config();
	~Config();
	void save();
	void load();
	void reset();
	bool testValidity();
	friend std::ostream& operator<<(std::ostream& os, const Config& c);
	friend std::istream& operator>>(std::istream& is, Config& c);
	void buySpaceship(int spaceship);
	void buyColor(int color);
	void addScore(float pts);
	void addNbrStar();
	void addXp(float pts);
	void addLvl();

	//Setters
	bool setVolume(int volume);
	bool setLevel(int lvl);
	bool setNbrStar(int nbrStar);
	void setMusic(bool music);
	void setVsync(bool vsync);
	bool setSelectedSpaceship(int spaceship);
	bool setSelectedColor(int color);
	std::string str();
	//Getters
	int getVolume() const;
	int getLevel() const ;
	float getXp() const;
	int getNbrStar() const;
	int getSelectedSpaceship() const;
	int getSelectedColor() const;
	bool isMusicOn() const;
	bool isVsyncOn() const;
	//Getters vector	
	std::vector<bool> getSpaceships() const;
	std::vector<bool> getColors() const;
	std::vector<int> getScores() const;
	std::vector<std::string> getDates() const;
	//String getters
	std::string getLevelString() const;
	std::string getNbrStarString() const;


};
