#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
	int keyTime = 5;
	sf::CircleShape player;
	//sf::Vector2f playerCenter = sf::Vector2f(player.getPosition().x, player.getPosition().y);

public:
	Player(float radius);
	sf::CircleShape getShape();
	//sf::Vector2f getCenter();

	const float getPositionX();
	const float getPositionY();

	void getPosition(sf::RenderWindow& window);
	void Movement(sf::RenderWindow& window); //Using Left and Right Key to Move
};
