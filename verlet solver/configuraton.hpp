#pragma once
#include <SFML/Graphics.hpp>

namespace conf 
{
	sf::Vector2u const window_size = { 1000, 1000 };
	sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
	unsigned int const framerate = 60;
	uint8_t const substeps = 8;
	float const deltaTime = 0.016f;
	sf::Vector2f const constraint_center = window_size_f / 2.f;
	float const constraint_radius = 500;
	float const soft_collision_factor = 0.05f;
	sf::Vector2u const grid_size = { 100, 100 };
}