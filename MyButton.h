#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#pragma once
class MyButton
{
private:
	bool _isSelected=false;
	int _toDo;
	sf::Texture texture, selectedTexture;
	sf::Sprite sprite;
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	MyButton() {};
	MyButton(std::string path);
	MyButton(std::string path, std::string pathSelected);
	~MyButton();
	void changeTexture(bool selected);
	void changeTexture();
	bool isSelected(int x, int y);
	//Setters
	void setPosition(int x, int y);
	void setToDo(int todo);
	void setVolume(int volume);
	//Getters
	sf::Sprite getSprite() const;
	int getX() const;
	int getY() const;
	int toDo() const;
};

