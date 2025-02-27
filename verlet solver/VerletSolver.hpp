#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "ball.hpp"
#include "configuraton.hpp"
#include "CollisionGrid.hpp"

class VerletSolver
{
public:
	VerletSolver();
	void add_ball(sf::Vector2f pos, sf::Vector2f accel, sf::Color color, float radius);
	void update(float deltaTime, uint8_t substeps);
	void render(sf::RenderWindow& window, sf::CircleShape& ball_shape);
	uint32_t get_ball_count();
	void moveBalls(sf::Vector2f attractionCenter, float radius, sf::Vector2f delta);
private:
	void remove_ball(uint32_t index);
	std::vector<Ball> ball_list;
	CollisionGrid collisionGrid;
	uint32_t ball_count = 0;
	sf::Vector2f gravity = { 0, 2.f };
	void update_ball_position(uint32_t index, float deltaTime);
	void update_positions(float deltaTime);
	void apply_gravity();
	void apply_constraint();
	void solve_collisions();
	void solve_collisions_soft();
	void release_hold();
};