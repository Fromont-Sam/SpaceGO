#include "Score.h"
#include <sstream>
#include <iostream>
#include <iomanip>

Score::Score(MyWindow* window) : Panel(window)
{
	//Init
	if (!font.loadFromFile("fonts/masterbreaker.ttf")) {}
	if (!title.loadFromFile("images/menu/btn_score.png")) {};
	if (!rank.loadFromFile("images/scoreboard/rank.png")) {};
	if (!score.loadFromFile("images/scoreboard/score.png")) {};
	if (!date.loadFromFile("images/scoreboard/date.png")) {};
	back = new MyButton("images/settings/back.png", "images/settings/back_s.png");

	_title = sf::Sprite(title);
	_rank = sf::Sprite(rank);
	_date = sf::Sprite(date);
	_score = sf::Sprite(score);

	for (size_t i = 0; i < 10; i++) {
		ranks.push_back(new sf::Text(getWindow()->getConfig()->getLevelString(), font, 50));
		scores.push_back(new sf::Text(getWindow()->getConfig()->getLevelString(), font, 50));
		dates.push_back(new sf::Text(getWindow()->getConfig()->getLevelString(), font, 50));
		ranks[i]->setFillColor(sf::Color(249, 148, 7));
		scores[i]->setFillColor(sf::Color(249, 148, 7));
		dates[i]->setFillColor(sf::Color(249, 148, 7));
	}

	//Init positions
	_title.setPosition(468,30);
	_rank.setPosition(331,142);
	_score.setPosition(636,142);
	_date.setPosition(1012,142);
	back->setPosition(23, 28);
}

Score::~Score()
{
	for (size_t i = 0; i < ranks.size(); i++) {
		delete ranks[i];
	}
	for (size_t i = 0; i < scores.size(); i++) {
		delete scores[i];
	}
	for (size_t i = 0; i < dates.size(); i++) {
		delete dates[i];
	}
	delete back;
}


void Score::init()
{
	getWindow()->clear();
	back->setVolume(getWindow()->getConfig()->getVolume());
	getWindow()->draw(getBackground());

	std::stringstream ssRank, ssScore, ssDate;
	for (size_t i = 0; i < 10; i++) {
		if (i < getWindow()->getConfig()->getScores().size()) {
			ssRank << "#" << i+1;
			ssScore << getWindow()->getConfig()->getScores()[i];
			ssDate << getWindow()->getConfig()->getDates()[i];
			

			ranks[i]->setString(ssRank.str());
			scores[i]->setString(ssScore.str());
			dates[i]->setString(ssDate.str());

			ranks[i]->setPosition(339, 172 + (61 * i));
			scores[i]->setPosition(750-scores[i]->getLocalBounds().width, 172 + (61 * i));
			dates[i]->setPosition(1106 - dates[i]->getLocalBounds().width, 172 + (61 * i));

			getWindow()->draw(*ranks[i]);
			getWindow()->draw(*scores[i]);
			getWindow()->draw(*dates[i]);

			ssRank.str(""); ssScore.str(""); ssDate.str("");
		}
	}
	getWindow()->draw(_title);
	getWindow()->draw(_rank);
	getWindow()->draw(_score);
	getWindow()->draw(_date);
	getWindow()->draw(back->getSprite());
}

int Score::keyPressedOnce(sf::Keyboard::Key key)
{
	switch (key) {
	case(sf::Keyboard::Key::Escape): return Panel::PANEL_MENU; break;
	}
	return -1;
}

int Score::keyPressed(int key)
{
	return -1;
}

int Score::mouseMove(int x, int y) {
	if (back->isSelected(x, y)) {
		back->changeTexture();
	}
	return -1;
}

int Score::mouseClicked(int x, int y, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left) {
		if (back->isSelected(x, y)) {
			return Panel::PANEL_MENU;
		}
	}
	return -1;
}

int Score::getType() const
{
	return Panel::PANEL_SCORE;
}
