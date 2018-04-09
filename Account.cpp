#include "Account.h"
#include "Spaceship.h"

/*
* Constructor
*/
Account::Account(MyWindow* window) : Panel(window)
{
	//Init
	if (!font.loadFromFile("fonts/masterbreaker.ttf")) {}
	if (!selectedColor.loadFromFile("images/account/selectedColor.png")) {};
	if (!xp.loadFromFile("images/account/exp_bar.png")) {};
	if (!star.loadFromFile("images/obstacles/star.png")) {};
	back = MyButton("images/settings/back.png", "images/settings/back_s.png");
	back.changeTexture(false);

	_selectedColor = sf::Sprite(selectedColor);
	_xp = sf::Sprite(xp);
	_star = sf::Sprite(star);

	level = sf::Text(getWindow()->getConfig()->getLevelString(), font, 120);
	nbrStar = sf::Text(getWindow()->getConfig()->getNbrStarString(), font, 80);

	rectXp = sf::RectangleShape(sf::Vector2f((int)(325 * getWindow()->getConfig()->getXp()), 33));
	rectXp.setFillColor(sf::Color(249, 148, 7));
	level.setFillColor(sf::Color(249, 148, 7));
	nbrStar.setFillColor(sf::Color(249, 148, 7));

	//Init vectors
	std::stringstream path, path2;
	MyButton tmp;
	int x, y;

	//Spaceships 
	for (size_t i = 0; i < 8; i++) {
		path.str("");
		path2.str("");
		path << "images/account/spaceship" << i << ".png";
		path2 << "images/account/spaceship" << i << "_s.png";
		tmp = MyButton(path.str(), path2.str());
		tmp.setVolume(getWindow()->getConfig()->getVolume());
		tmp.setToDo(i);
		x = 437 + ((i % 4) * 157);
		y = 340 + ((i / 4) * 171);
		tmp.setPosition(x, y);
		spaceships.push_back(tmp);
	}
	tmp = MyButton("images/account/spaceship8.png", "images/account/spaceship8_s.png");
	tmp.setPosition(1048, 451);
	tmp.setToDo(8);
	spaceships.push_back(tmp);
	//Colors 
	for (size_t i = 0; i < 7; i++) {
		path.str("");
		path2.str("");
		path << "images/account/color.png";
		path2 << "images/account/color" << i << ".png";
		tmp = MyButton(path.str(), path2.str());
		tmp.setVolume(getWindow()->getConfig()->getVolume());
		tmp.setToDo(i);
		x = 449 + (i * 85);
		tmp.setPosition(x, 653);
		colors.push_back(tmp);
	}

	//Init positions
	level.setPosition(712-level.getLocalBounds().width/2, 21);
	nbrStar.setPosition(710-nbrStar.getLocalBounds().width/2, 192);
	_xp.setPosition(567, 168);
	_star.setPosition(718 + nbrStar.getLocalBounds().width, 220);
	rectXp.setPosition(570, 171);
	back.setPosition(23, 28);
}

/*
* Draw and position all sprites in the panel
*/
void Account::init()
{
	level.setString(getWindow()->getConfig()->getLevelString());
	nbrStar.setString(getWindow()->getConfig()->getNbrStarString());
	level.setPosition(702 - level.getLocalBounds().width / 2, 21);
	nbrStar.setPosition(680 - nbrStar.getLocalBounds().width / 2, 192);
	_star.setPosition(688 + nbrStar.getLocalBounds().width / 2, 220);
	rectXp.setSize(sf::Vector2f((int)(325 * getWindow()->getConfig()->getXp()), 33));
	back.setVolume(getWindow()->getConfig()->getVolume());

	getWindow()->clear();
	getWindow()->draw(getBackground());

	for (size_t i = 0; i < spaceships.size(); i++) {
		if (i == getWindow()->getConfig()->getSelectedSpaceship()) {
			spaceships[i].changeTexture(true);
		}
		else {
			spaceships[i].changeTexture(false);
		}
		getWindow()->draw(spaceships[i].getSprite());
	}
	for (size_t i = 0; i < colors.size(); i++) {
		if (getWindow()->getConfig()->getColors()[getWindow()->getConfig()->getSelectedSpaceship()]) {
			colors[i].changeTexture(true);
		}
		else {
			colors[i].changeTexture(false);
		}
		if (i == getWindow()->getConfig()->getSelectedColor()) {
			_selectedColor.setPosition(444 + (i * 85), 648);
		}
		getWindow()->draw(colors[i].getSprite());
	}

	getWindow()->draw(level);
	getWindow()->draw(nbrStar);
	getWindow()->draw(_star);
	getWindow()->draw(rectXp);
	getWindow()->draw(_xp);
	getWindow()->draw(back.getSprite());
	getWindow()->draw(_selectedColor);
}

/*
* Keyboard listener (key pressed once) 
*/
int Account::keyPressedOnce(sf::Keyboard::Key key)
{
	switch (key) {
	case(sf::Keyboard::Key::Escape): return Panel::PANEL_MENU; break;
	}
	return -1;
}

/*
* Mouse listener (mouse moved)
*/
int Account::mouseMove(int x, int y) {
	if (back.isSelected(x, y)) {
		back.changeTexture();
	}
	return -1;
}

/*
* Mouse listener (mouse pressed)
*/
int Account::mouseClicked(int x, int y, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left) {
		if (back.isSelected(x, y)) {
			back.changeTexture();
			return Panel::PANEL_MENU;
		}
		else {
			for (size_t i = 0; i < spaceships.size(); i++) {
				if (spaceships[i].isSelected(x, y) && getWindow()->getConfig()->setSelectedSpaceship(i)) {
					spaceships[i].changeTexture();
					getWindow()->getConfig()->setSelectedSpaceship(i);
					if (getWindow()->getConfig()->getColors()[i] == true) {
						for (size_t j = 0; j < colors.size(); j++) {
							colors[j].changeTexture(true);
						}
					}
					else {
						for (size_t j = 0; j < colors.size(); j++) {
							colors[j].changeTexture(false);
						}
						getWindow()->getConfig()->setSelectedColor(i);
					}
				}
			}
			for (size_t i = 0; i < colors.size(); i++) {
				if (colors[i].isSelected(x, y) && getWindow()->getConfig()->setSelectedColor(i)) {
					getWindow()->getConfig()->setSelectedColor(i);
				}
			}
		}
	}
	return -1;
}
/*
* Return the panel type as an int
*/

int Account::getType() const
{
	return Panel::PANEL_ACCOUNT;
}
