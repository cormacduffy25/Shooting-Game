#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
	int keyTime = 5;
	sf::CircleShape player;

public:
	Player(float radius);
	sf::CircleShape getShape();

	void Movement(sf::RenderWindow& window); //Using Left and Right Key to Move
};
