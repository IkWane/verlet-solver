#pragma once
#include <SFML/Graphics.hpp>

namespace conf 
{
	sf::Vector2u const window_size = { 800, 600 };
	sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
	float const framerate = 60;
	float const circle_radius = 10.f;
}