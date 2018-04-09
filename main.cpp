#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "Panel.h"
#include "Splashscreen.h"
#include "Menu.h"
#include "Game.h"
#include "Settings.h"
#include "Shop.h"
#include "Score.h"
#include "Account.h"
#include "Credits.h"

#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#pragma warning (disable : 4018)

int main()
{
	//Window variables
	int ticks = 0;
	FreeConsole(); //Hide console

	//Init window
	MyWindow window(sf::VideoMode(1440, 810, 0), "SpaceGO", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Image image;
	image.loadFromFile("images/icon.png");
	window.setIcon(128,128, image.getPixelsPtr());

	//Init music
	sf::Music music;
	if (!music.openFromFile("sounds/music.wav"))
	{}
	music.setLoop(true);
	music.setVolume(0);
	music.play();
	
	//Init panels
	int activePanel = 0;
	std::vector<Panel*> panels;
	panels.push_back(new Splashscreen(&window));
	panels.push_back(new Menu(&window));
	panels.push_back(new Game(&window));
	panels.push_back(new Settings(&window));
	panels.push_back(new Shop(&window));
	panels.push_back(new Score(&window));
	panels.push_back(new Account(&window));
	panels.push_back(new Credits(&window));

	//Program running
	while (window.isOpen())
	{
		sf::Event event;
		if (window.getConfig()->isMusicOn()) {
			music.setVolume(window.getConfig()->getVolume());
		}
		else {
			music.setVolume(0);
		}
		window.setVerticalSyncEnabled(window.getConfig()->isVsyncOn());
		//Event manager
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: 
				window.getConfig()->save();
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (panels[activePanel]->keyPressedOnce(event.key.code)!=-1) {
					activePanel = panels[activePanel]->keyPressedOnce(event.key.code);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (panels[activePanel]->mouseClicked(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button) >= 0) {
					activePanel = panels[activePanel]->mouseClicked(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
				}
				break;
			case sf::Event::MouseMoved:
				if (panels[activePanel]->mouseMove(event.mouseMove.x, event.mouseMove.y) >= 0) {
					activePanel = panels[activePanel]->mouseMove(event.mouseMove.x, event.mouseMove.y);
				}
				break;
			}
		}
		//Background animation
		panels[activePanel]->moveBackground();
		if (panels[activePanel]->getType() == Panel::PANEL_SPLASHSCREEN) {
			ticks++;
			if (ticks >= 30) {
				panels[activePanel]->blink();
				ticks = 0;
			}
		}

		//Keys manager
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			panels[activePanel]->keyPressed(sf::Keyboard::Z);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			panels[activePanel]->keyPressed(sf::Keyboard::S);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			panels[activePanel]->keyPressed(sf::Keyboard::Q);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			panels[activePanel]->keyPressed(sf::Keyboard::D);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			panels[activePanel]->keyPressed(sf::Keyboard::Space);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			panels[activePanel]->keyPressed(sf::Keyboard::R);
		}

		//Init view
		window.clear();
		panels[activePanel]->init();
		window.display();
	}

	return 0;
}