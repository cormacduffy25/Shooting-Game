#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include<cstdlib>
#include <vector>

/*
		~~~RULES OF THE GAME~~~
* Use the LEFT and RIGHT keys to MOVE the ship
* Use the SPACE bar to SHOOT the enemy ships
*/

/*
*		~~~IDEAS and TODO LIST~~~
* - All the Objects and Functions into Classes (ccp & header files)
* - Change the shapes into Sprites for the game 
* - Moveable background/wallpaper to make illusion that ship is flying and going foward
* - Scores/Highscores 
* - Way to Lose the Game 
* - Audio
* 
* Youtube Videos I used for creating it 
* https://www.youtube.com/watch?v=BNH96H7DW90 - SFML C++ Tutorial 06 | Simple game using WASD and Mouse!
* https://www.youtube.com/watch?v=DZOCzW9e6Qs - SFML C++ Tutorial 08 | Shooter game with many projectiles and enemies!
* 
* Suraj Sharma is really good Youtube Channel for making SFML game Tutorials :D
*/

using namespace sf;

void Movement(int &keyTime, CircleShape &player, RenderWindow &window); //function for Player's movement on the x axis 

void Shoot(int& shootTimer, Sound& pew, CircleShape& projectile, std::vector<CircleShape>& projectiles, Vector2f& playerCenter);

void EnemySpwaner(int& enemySpawnTimer, RectangleShape& enemy, std::vector<RectangleShape>& enemies, RenderWindow& window);

int main()
{
		//Audio
		SoundBuffer pewBuffer, boomBuffer;

		if (!pewBuffer.loadFromFile("laserRetro_000.ogg"))
			return -1;

		if (!boomBuffer.loadFromFile("explosionCrunch_000.ogg"))
			return -1;

		Sound pew, boom;
		pew.setBuffer(pewBuffer);
		boom.setBuffer(boomBuffer);


	int keyTime = 5; //This is KeyFrames

	srand(time(NULL)); //To Create a Random Seed for each game 

	sf::RenderWindow window(sf::VideoMode(640, 480), "Ball Shooter");
	window.setFramerateLimit(60);

	//Objects - Projectile, Enemy and Player (This need to be in Classes)

	CircleShape projectile;
	projectile.setFillColor(Color::Red);
	projectile.setRadius(5.f);

	RectangleShape enemy;
	enemy.setFillColor(Color::Magenta);
	enemy.setSize(Vector2f(50.f, 50.f));

	CircleShape player;
	player.setFillColor(Color::White);
	player.setRadius(50.f);
	player.setOrigin(player.getRadius(), player.getRadius());
	player.setPosition(window.getSize().x / 2, window.getSize().y- 70);
	Vector2f playerCenter;
	int shootTimer = 0;

	//This is to create nultiple of projectiles at once, same as for the enemies 
	std::vector<CircleShape> projectiles;
	projectiles.push_back(CircleShape(projectile));

	std::vector<RectangleShape> enemies;
	enemies.push_back(RectangleShape(enemy));
	int enemySpawnTimer = 0;

	//~~~EVENT~~~

	sf::Event event;
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();

			}
		}

		//~~~UPDATE~~~

		//player
		playerCenter = Vector2f(player.getPosition().x, player.getPosition().y); //Finding the Centre Area of Player
		Movement(keyTime, player, window);

		//projectiles

		Shoot(shootTimer, pew, projectile, projectiles, playerCenter);

		//enemies

		EnemySpwaner(enemySpawnTimer, enemy, enemies, window);

		//Collision
		if (!enemies.empty() && !projectiles.empty()) //When the projectile hits the enemy, enemy object will be erase
		{
			for (size_t i = 0; i < projectiles.size(); i++)
			{
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						projectiles.erase(projectiles.begin() + i);
						enemies.erase(enemies.begin() + k);
						boom.play();
						break;
					}
				}
			}
		}

		//Close Game

		if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			// quit...
			// Someone closed the window- bye
			window.close();
		}

		//~~~DRAW~~~
		window.clear();

		window.draw(player);

		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}

		for (size_t i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i]);
		}

		window.display();
	}
	return 0; 
}


//~~~FUNCTIONS~~~
void Movement(int& keyTime, CircleShape& player, RenderWindow &window) //Using Left and Right Key to Move
{
	if (keyTime < 5)
		keyTime++;

	if (Keyboard::isKeyPressed(Keyboard::Left) && player.getPosition().x - player.getRadius() > 0 ) {
		player.move(-10.f, 0.f);
		keyTime = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && player.getPosition().x +player.getRadius() < window.getSize().x) {
		player.move(10.f, 0.f);
		keyTime = 0;
	}
} 

void Shoot(int& shootTimer, Sound& pew, CircleShape& projectile, std::vector<CircleShape>& projectiles, Vector2f& playerCenter) //Shooting Function
{
	if (shootTimer < 5)
		shootTimer++;

	if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 5) //Shoot using the Space Bar
	{
		projectile.setPosition(playerCenter);
		projectiles.push_back(CircleShape(projectile));

		pew.play();

		shootTimer = 0;
	}

	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].move(0.f, -10.f);

		if (projectiles[i].getPosition().y <= 0)
			projectiles.erase(projectiles.begin() + i);
	}
}

void EnemySpwaner(int& enemySpawnTimer, RectangleShape& enemy, std::vector<RectangleShape>& enemies, RenderWindow& window)
{
	if (enemySpawnTimer < 15) //Spawns the amount of enemies onto the screen. 15 is the max
		enemySpawnTimer++;

	if (enemySpawnTimer >= 15)
	{
		enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f); //this is to make enemies appear random on the top of the screen 
		enemies.push_back(RectangleShape(enemy));

		enemySpawnTimer = 0;
	}


	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].move(0.f, 5.f);

		if (enemies[i].getPosition().y > window.getSize().y)
			enemies.erase(enemies.begin() + i);
	}
}
