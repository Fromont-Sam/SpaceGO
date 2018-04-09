#include "Shop.h"

Shop::Shop(MyWindow* window) : Panel(window)
{
	std::stringstream path, path2;
	MyButton *tmp;
	int x, y;
	for (size_t i = 0; i < 15; i++) {
		path.str("");
		path2.str("");
		path << "images/shop/card" << i << ".png";
		path2 << "images/shop/card" << i << "_s.png";
		tmp = new MyButton(path.str() , path2.str());
		tmp->setVolume(getWindow()->getConfig()->getVolume());
		tmp->setToDo(i);
		x = 79 + ((i % 5) * 258);
		y = 171 + ((i / 5) * 214);
		tmp->setPosition(x,y);
		cards.push_back(tmp);
	}
	if (!shop.loadFromFile("images/menu/btn_shop.png")) {};
	if (!star.loadFromFile("images/obstacles/star.png")) {};
	back = new MyButton("images/settings/back.png", "images/settings/back_s.png");
	back->setVolume(getWindow()->getConfig()->getVolume());
	if (!font.loadFromFile("fonts/masterbreaker.ttf")) {}

	_shop = sf::Sprite(shop);
	_star = sf::Sprite(star);

	_shop.setPosition(435, 52);
	_star.setPosition(1356, 14);
	back->setPosition(23, 28);

	_nbrStar = sf::Text(getWindow()->getConfig()->getNbrStarString(), font, 80);
	_nbrStar.setFillColor(sf::Color(249, 148, 7));
	_nbrStar.setPosition(1265, -10);
}

Shop::~Shop()
{
	for (size_t i = 0; i < cards.size(); i++) {
		delete cards[i];
	}
	delete back;
}

void Shop::init()
{
	_nbrStar.setString(getWindow()->getConfig()->getNbrStarString());
	getWindow()->clear();
	getWindow()->draw(getBackground());
	getWindow()->draw(_shop);
	getWindow()->draw(_star);
	getWindow()->draw(_nbrStar);
	getWindow()->draw(back->getSprite());
	for (size_t i = 0; i < cards.size(); i++) {
		if (i != 0) {
			if ((i % 2) == 0 && getWindow()->getConfig()->getColors()[i / 2]) {
				cards[i]->changeTexture();
			}
			else if ((i % 2) != 0 && getWindow()->getConfig()->getSpaceships()[i / 2 + 1]) {
				cards[i]->changeTexture();
			}
		}
		else {
			if (getWindow()->getConfig()->getColors()[8]) {
				cards[i]->changeTexture();
			}
		}
		getWindow()->draw(cards[i]->getSprite());
	}
}

int Shop::keyPressedOnce(sf::Keyboard::Key key)
{
	switch (key) {
	case(sf::Keyboard::Key::Escape): return Panel::PANEL_MENU; break;
	}
	return -1;
}

int Shop::mouseClicked(int x, int y, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left) {
		if (back->isSelected(x, y)) {
			return Panel::PANEL_MENU;
		}
		else {
			for (size_t i = 0; i < cards.size(); i++) {
				if (cards[i]->isSelected(x, y)) {
					if (i != 0) {
						if ((i % 2) == 0) {
							getWindow()->getConfig()->buyColor(i / 2);
						}
						else if ((i % 2) != 0) {
							getWindow()->getConfig()->buySpaceship(i / 2 + 1);
						}
					}
					else {
						getWindow()->getConfig()->buyColor(8);
					}
				}
			}
		}
	}
	return -1;
}

int Shop::mouseMove(int x, int y) {
	if (back->isSelected(x, y)) {
		back->changeTexture();
	}
	return -1;
}

int Shop::getType() const
{
	return Panel::PANEL_SHOP;
}
