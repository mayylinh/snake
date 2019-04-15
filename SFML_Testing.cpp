#include "stdafx.h"
#include <SFML/Graphics.hpp> //using namespace sf
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>

//globals dimensions for window
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox;	//background number of pixels in width
int h = size * num_vertBox;	//background number of pixels in height

float delay = 0.1f;
int random = 0;
sf::Texture t1, t2, t3, t4, t5, t6, t7, t8, t9;
sf::Sprite sprite1, sprite2, sprite3, sprite4, sprite5, sprite6, sprite7, sprite8, sprite9;

//create the snake
int direction, snake1_length = 4, score1 = snake1_length - 4;
int snake2_length = 4, score2 = snake2_length - 4;

//maximum snake size 100
struct Snake
{
	int x, y;
} s1[100], s2[100];

struct Fruit
{
	int x, y;
} food;

//updating as snake moves
void move()
{
	/*move the body*/
	for (int i = snake1_length; i > 0; i--)
	{
		s1[i].x = s1[i - 1].x;
		s1[i].y = s1[i - 1].y;
	}

	for (int i = snake2_length; i > 0; i--)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}


	/*head of snake, s[0], depends on directions user inputs*/
	//if user presses up
	if (direction == 0)
		s1[0].y -= 1;

	//if user presses down
	if (direction == 1)
		s1[0].y += 1;

	//if user presses left
	if (direction == 2)
		s1[0].x -= 1;

	//if user presses right
	if (direction == 3)
		s1[0].x += 1;

	//if user presses W
	if (direction == 4)
		s2[0].y -= 1;

	//if user presses S
	if (direction == 5)
		s2[0].y += 1;

	//if user presses A
	if (direction == 6)
		s2[0].x -= 1;

	//if user presses D
	if (direction == 7)
		s2[0].x += 1;

	//if snake eats food it should grow 
	//check if snake head = food location 
	if (((s1[0].x) == food.x) && ((s1[0].y) == food.y))
	{
		//increment snake 
		snake1_length++;

		//Randomly place food somewhere else 
		random = (std::rand() % (5 - 0 + 1));
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		//snake moves faster
		delay -= 0.005f;

		//increase score
		score1++;
	}

	if (((s2[0].x) == food.x) && ((s2[0].y) == food.y))
	{
		//increment snake 
		snake2_length++;

		//Randomly place food somewhere else 
		random = (std::rand() % (5 - 0 + 1));
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		//snake moves faster
		delay -= 0.005f;

		//increase score
		score2++;
	}

	/*boundary checking snake as it hits screen end
	loop snake back on other side */
	//LEFT and RIGHT 
	if (s1[0].x > num_horzBox)
		s1[0].x = 0;
	if (s1[0].x < 0)
		s1[0].x = num_horzBox;
	//TOP and BOTTOM 
	if (s1[0].y > num_vertBox)
		s1[0].y = 0;
	if (s1[0].y < 0)
		s1[0].y = num_vertBox;

	if (s2[0].x > num_horzBox)
		s2[0].x = 0;
	if (s2[0].x < 0)
		s2[0].x = num_horzBox;
	//TOP and BOTTOM 
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;
	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	//check if you eat body of snake 
	for (int i = 1; i < snake1_length; i++)
	{
		//cut snake body from place eaten 
		if (s1[0].x == s1[i].x && s1[0].y == s1[i].y)
		{
			snake1_length = i;
			delay = 0.1f;
			score1 = i - 4;
		}
	}
	
	for (int i = 1; i < snake2_length; i++)
	{
		//cut snake body from place eaten 
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y)
		{
			snake2_length = i;
			delay = 0.1f;
			score2 = i - 4;
		}
	}
}

int main()
{
	//setting pseudorandom time
	srand(time(0));

	//window that we can play the game in
	sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

	//textures load an image into the GPU
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	t4.loadFromFile("images/apple.png");
	t5.loadFromFile("images/lemon.png");
	t6.loadFromFile("images/orange.png");
	t7.loadFromFile("images/pear.png");
	t8.loadFromFile("images/watermelon.png");
	t9.loadFromFile("images/mushroom.png");

	//sprite has physical dimensions
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	sf::Sprite sprite4(t4);
	sf::Sprite sprite5(t5);
	sf::Sprite sprite6(t6);
	sf::Sprite sprite7(t7);
	sf::Sprite sprite8(t8);
	sf::Sprite sprite9(t9);

	//initially place food somewhere on screen
	food.x = 10;
	food.y = 10;

	sf::Clock clock;
	float timer = 0.0f;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event e;

		while (window.pollEvent(e))
		{
			//check when the window is closed
			if (e.type == sf::Event::Closed)
				window.close();
		}

		//control for snake by user
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction = 3; 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			direction = 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			direction = 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			direction = 6;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			direction = 7;

		
		if (timer > delay)
		{
			timer = 0; //reset timer
			move(); //move snake one forward
		}

		//draw in window
		window.clear(); //get rid of all frame

		//draw background
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				sprite1.setPosition(i * size, j * size);
				window.draw(sprite1);
			}
		}

		//then draw snake otherwise background will be drawn over snake
		for (int i = 0; i < snake1_length; i++)
		{
			if (score1 < 5)
			{
				sprite2.setPosition(s1[i].x * size, s1[i].y * size);
				window.draw(sprite2);
			}
			else
			{
				sprite3.setPosition(s1[i].x * size, s1[i].y * size);
				window.draw(sprite3);
			}
		}

		for (int i = 0; i < snake2_length; i++)
		{
			if (score2 < 5)
			{
				sprite2.setPosition(s2[i].x * size, s2[i].y * size);
				window.draw(sprite2);
			}
			else
			{
				sprite3.setPosition(s2[i].x * size, s2[i].y * size);
				window.draw(sprite3);
			}
		} 

		// draw fruit last
		sf::Sprite fruits[6] = { sprite4, sprite5, sprite6, sprite7, sprite8, sprite9 };
		fruits[random].setPosition(food.x * size, food.y * size);
		
		window.draw(fruits[random]);

		window.display();
	}

	if (!window.isOpen())
	{
		std::cout << "Player 1 Score: " << std::to_string(score1) << std::endl;
		std::cout << "Player 2 Score: " << std::to_string(score2);
	}

	return 0;
}