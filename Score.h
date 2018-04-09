#include "Panel.h"
#include "MyButton.h"
#pragma once
class Score : public Panel
{
private:
	sf::Font font;
	sf::Texture title, rank, score, date;
	sf::Sprite _title, _rank, _score, _date;
	std::vector<sf::Text*> ranks, scores, dates;
	MyButton *back;
public:
	Score(MyWindow* window);
	~Score();
	void init();
	//Listeners
	int keyPressedOnce(sf::Keyboard::Key key);
	int keyPressed(int key);
	int mouseMove(int x, int y);
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	//Getters
	int getType() const;
};