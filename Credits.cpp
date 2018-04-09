#include "Credits.h"

Credits::Credits(MyWindow* window) : Panel(window)
{
	//Init
	if (!font.loadFromFile("fonts/masterbreaker.ttf")) {}
	back = MyButton("images/settings/back.png", "images/settings/back_s.png");
	back.changeTexture(false); 

	ln1 = sf::Text("Jeu réalisé par FROMONT Sam, LECLERCQ Noe, BARON Alexandre", font, 50);
	ln2 = sf::Text("etudiants de la HELHa Campus Mons,", font, 50);
	ln3 = sf::Text("dans le cadre du cours de Mr. V. Altares.", font, 50);

	ln1.setFillColor(sf::Color(249, 148, 7));
	ln2.setFillColor(sf::Color(249, 148, 7));
	ln3.setFillColor(sf::Color(249, 148, 7));

	back.setPosition(23, 28);
	ln1.setPosition(710 - ln1.getLocalBounds().width / 2, 300);
	ln2.setPosition(710 - ln2.getLocalBounds().width / 2, 400);
	ln3.setPosition(710 - ln3.getLocalBounds().width / 2, 500);
}

void Credits::init()
{
	back.setVolume(getWindow()->getConfig()->getVolume());

	getWindow()->clear();
	getWindow()->draw(getBackground());
	getWindow()->draw(back.getSprite());
	getWindow()->draw(ln1);
	getWindow()->draw(ln2);
	getWindow()->draw(ln3);
}

int Credits::keyPressedOnce(sf::Keyboard::Key key)
{
	switch (key) {
	case(sf::Keyboard::Key::Escape): return Panel::PANEL_MENU; break;
	}
	return -1;
}

int Credits::keyPressed(int key)
{
	return -1;
}

int Credits::mouseMove(int x, int y) {
	if (back.isSelected(x, y)) {
		back.changeTexture();
	}
	return -1;
}

int Credits::mouseClicked(int x, int y, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left) {
		if (back.isSelected(x, y)) {
			back.changeTexture();
			return Panel::PANEL_MENU;
		}
	}
	return -1;
}

int Credits::getType() const
{
	return Panel::PANEL_ACCOUNT;
}
