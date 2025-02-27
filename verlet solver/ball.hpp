#pragma once
#include <SFML/Graphics.hpp>

struct Ball
{
	sf::Vector2f position;
	sf::Vector2f prev_position;
	sf::Vector2f acceleration;
	sf::Color color;
	float radius;
	bool positionUpdate;
};