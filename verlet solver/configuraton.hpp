#pragma once
#include <SFML/Graphics.hpp>

namespace conf 
{
	sf::Vector2u const window_size = { 800, 600 };
	sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
	unsigned int const framerate = 60;
	float const circle_radius = 5.f;
	uint8_t const substeps = 8;
	sf::Vector2f const constraint_center = window_size_f / 2.f;
	float const constraint_radius = 250;
}