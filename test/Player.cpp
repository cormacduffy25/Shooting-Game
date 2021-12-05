#include "Player.h"
Player::Player(float radius) {
	player.setRadius(50.f);
	player.setOrigin(player.getRadius(), player.getRadius());
	player.setFillColor(sf::Color::White);
}

sf::CircleShape Player::getShape()
{
	return player;
}

void Player::Movement(sf::RenderWindow& window) //Using Left and Right Key to Move
{
	if (keyTime < 5)
		keyTime++;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x - player.getRadius() > 0) {
		player.move(-10.f, 0.f);
		keyTime = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x + player.getRadius() < window.getSize().x) {
		player.move(10.f, 0.f);
		keyTime = 0;
	}
}