#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "ball.hpp"
#include "configuraton.hpp"

class VerletSolver
{
public:
	void add_ball(sf::Vector2f pos, sf::Vector2f accel);
	void update(float deltaTime, uint8_t substeps);
	void render(sf::RenderWindow* window, sf::CircleShape* ball_shape);
private:
	void remove_ball(uint32_t index);
	std::vector<Ball> ball_list;
	uint32_t ball_count = 0;
	sf::Vector2f gravity = { 0, 500.f };
	void update_ball_position(uint32_t index, float deltaTime);
	void update_positions(float deltaTime);
	void apply_gravity();
	void apply_constraint();
};