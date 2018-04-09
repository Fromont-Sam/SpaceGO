#include "Config.h"
#include "Spaceship.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

/*
* Constructor
*/
Config::Config()
{
	load();
}

/*
* Destructor
*/
Config::~Config()
{}

/*
* Save the current configuration
*/
void Config::save()
{
	if (_noReset == 0 || _lvl<=0) {
		reset();
	}
	std::ofstream ofs("config.cfg");
	ofs << *this;
	ofs.close();
}

/*
* Load the last configuration
*/
void Config::load() {
	std::ifstream ifs("config.cfg");
	ifs >> *this;
}

/*
* Reset the current configuration
*/
void Config::reset()
{
	_noReset = true;
	_volume = 50;
	_lvl = 1;
	_xp = 0;
	_nbrStar = 0;
	_sSpaceship = 0;
	_sColor = 0;
	_music = true;
	_vsync = true;
	spaceships = {true, false, false, false, false, false, false, false, true};
	colors = { true, false, false, false, false, false, false, false, false };
	scores = {};
	dates = {};
}

/*
* Overwrite << operator to print configuration in a file 
*/
std::ostream& operator<<(std::ostream& os, const Config& c)
{
	os << c._noReset << '\n';
	os << c._volume << '\n';
	os << c._lvl << '\n';
	os << c._xp << '\n';
	os << c._nbrStar << '\n';
	os << c._sSpaceship << '\n';
	os << c._sColor << '\n';
	os << c._music << '\n';
	os << c._vsync << '\n';
	os << c.getSpaceships().size() << '\n';
	for (size_t i = 0; i < c.getSpaceships().size(); i++) {
		os << c.getSpaceships()[i] << '\n';
	}
	os << c.getColors().size() << '\n';
	for (size_t i = 0; i < c.getColors().size(); i++) {
		os << c.getColors()[i] << '\n';
	}
	os << c.getScores().size() << '\n';
	for (size_t i = 0; i < c.getScores().size(); i++) {
		os << c.getScores()[i] << '\n';
	}
	os << c.getDates().size() << '\n';
	for (size_t i = 0; i < c.getDates().size(); i++) {
		os << c.getDates()[i] << '\n';
	}
	return os;
}

/*
* Overwrite >> operator to read configuration in a file
*/
std::istream& operator>>(std::istream& is, Config& c)
{
	int n = 0, tmpInt;
	std::string tmpString;
	is >> c._noReset >> c._volume >> c._lvl >> c._xp  >> c._nbrStar >> c._sSpaceship >> c._sColor >> c._music >> c._vsync;
	if (c._noReset == 0 || c._lvl <= 0) {
		c.reset();
		return is;
	}
	is >> n;
	for (size_t i = 0; i < n; i++) {
		is >> tmpInt;
		c.spaceships.push_back(tmpInt);
	}
	is >> n;
	for (size_t i = 0; i < n; i++) {
		is >> tmpInt;
		c.colors.push_back(tmpInt);
	}
	is >> n;
	for (size_t i = 0; i < n; i++) {
		is >> tmpInt;
		c.scores.push_back(tmpInt);
	}
	is >> n;
	for (size_t i = 0; i < n; i++) {
		is >> tmpString;
		c.dates.push_back(tmpString);
		tmpString = "";
	}
	return is;
}

/*
* Update configuration when you buy a spaceship
*/
void Config::buySpaceship(int spaceship)
{
	if (_nbrStar>=15 && spaceship > 0 && spaceship < 9 && !spaceships[spaceship]) {
		_nbrStar -= 15;
		spaceships[spaceship] = true;
	}
}

/*
* Update configuration when you buy a spaceship
*/
void Config::buyColor(int color)
{
	if (_nbrStar >= 10 && color > 0 && color < 9 && !colors[color]) {
		_nbrStar -= 10;
		colors[color] = true;
	}
}

/*
* Update configuration when you do a new score
*/
void Config::addScore(float pts)
{
	auto time = std::time(nullptr);
	int score = (int)pts;
	int tmp;
	std::string tmpd;
	std::stringstream date;
	date << std::put_time(std::gmtime(&time), "%D");
	if (score > 0) {
		scores.push_back(score);
		dates.push_back(date.str());
		for (size_t i = 0; i < scores.size(); i++)  {
			for (size_t j = i + 1; j < scores.size(); j++) {                  
				if (scores[j] > scores[i])	{
					tmp = scores[i];
					scores[i] = scores[j];
					scores[j] = tmp;
					tmpd = std::string(dates[i]);
					dates[i] = std::string(dates[j]);
					dates[j] = std::string(tmpd);
				}
			}
		}
		while (scores.size() > 10) {
			scores.pop_back();
			dates.pop_back();
		}
	}
}

//Setters and getters
void Config::addNbrStar()
{
	_nbrStar++;
}

void Config::addXp(float pts)
{
	int toAdd = (int) (pts / 100.);
	_xp += toAdd;
	if (_xp >= 100) {
		addLvl();
		_xp %= 100;
	}
}

void Config::addLvl()
{
	if (_lvl < 100) {
		_lvl++;
	}
}

std::vector<bool> Config::getSpaceships() const
{
	return std::vector<bool>(spaceships);
}

std::vector<bool> Config::getColors() const
{
	return std::vector<bool>(colors);
}

std::vector<int> Config::getScores() const
{
	return std::vector<int>(scores);
}

std::vector<std::string> Config::getDates() const
{
	return std::vector<std::string>(dates);
}

int Config::getVolume() const
{
	return _volume;
}


int Config::getLevel() const
{
	return _lvl;
}

float Config::getXp() const
{
	return (_xp/100.);
}

int Config::getNbrStar() const
{
	return _nbrStar;
}

int Config::getSelectedSpaceship() const
{
	return _sSpaceship;
}

int Config::getSelectedColor() const
{
	return _sColor;
}

bool Config::isMusicOn() const
{
	return _music;
}

bool Config::isVsyncOn() const
{
	return _vsync;
}

std::string Config::getLevelString() const
{
	std::stringstream ss;
	ss.width(8);
	ss << "Level " << _lvl;
	return ss.str();
}

std::string Config::getNbrStarString() const
{
	std::stringstream ss;
	ss.width(3);
	ss << _nbrStar;
	return ss.str();
}

bool Config::setVolume(int volume)
{
	if (volume >= 0 && volume <= 100) {
		_volume = volume;
		return true;
	}
	return false;
}

bool Config::setLevel(int lvl)
{
	if (lvl > 0) {
		_lvl = lvl;
		return true;
	}
	return false;
}

bool Config::setNbrStar(int nbrStar)
{
	if (nbrStar >= 0) {
		_nbrStar = nbrStar;
		return true;
	}
	return false;
}

void Config::setMusic(bool music)
{
	_music = music;
}

void Config::setVsync(bool vsync)
{
	_vsync = vsync;
}

bool Config::setSelectedSpaceship(int spaceship)
{
	if (spaceship >= 0 && spaceship <= 8 && spaceships[spaceship]) {
		_sSpaceship = spaceship;
		return true;
	}
	return false;
}

bool Config::setSelectedColor(int color)
{
	if (color >= 0 && color <= 7 && colors[_sSpaceship]) {
		_sColor = color;
		return true;
	}
	_sColor = Spaceship::SPACESHIP_COLOR_RED;
	return false;
}

std::string Config::str() {
	std::stringstream ss;
	ss << "Volume : " << _volume << std::endl;
	ss << "Lvl : " << _lvl << std::endl;
	ss << "Xp : " << _xp << std::endl;
	ss << "Nbr Stars : " << _nbrStar << std::endl;
	ss << "Music : " << _music << std::endl;
	ss << "Vsync : " << _vsync << std::endl;
	for (size_t i = 0; i < spaceships.size(); i++) {
		ss << "Spaceships : " << spaceships[i] << std::endl;
	}
	for (size_t i = 0; i < colors.size(); i++) {
		ss << "Colors : " << colors[i] << std::endl;
	}
	for (size_t i = 0; i < scores.size(); i++) {
		ss << "Scores : " << scores[i] << std::endl;
	}
	for (size_t i = 0; i < dates.size(); i++) {
		ss << "Dates : " << dates[i] << std::endl;
	}
	return ss.str();
}
