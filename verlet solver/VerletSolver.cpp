#include "VerletSolver.hpp"
#include <iostream>

void VerletSolver::add_ball(sf::Vector2f pos, sf::Vector2f accel)
{
	this->ball_list.push_back({ pos, pos, accel });
	this->ball_count++;
}

void VerletSolver::update(float deltaTime, uint8_t substeps)
{
	for (uint8_t i = 0; i < substeps; i++)
	{
		apply_gravity();
		update_positions(deltaTime / substeps);
		apply_constraint();
	}
}

void VerletSolver::render(sf::RenderWindow* window, sf::CircleShape* ball_shape)
{
	for (auto& ball : this->ball_list)
	{
		ball_shape->setPosition(ball.position);
		window->draw(*ball_shape);
	}
}

void VerletSolver::remove_ball(uint32_t index)
{
	this->ball_list.erase(ball_list.begin() + index);
}

void VerletSolver::update_ball_position(uint32_t index, float deltaTime)
{
	sf::Vector2f vel = this->ball_list[index].position - this->ball_list[index].prev_position;
	vel += this->ball_list[index].acceleration * deltaTime * deltaTime;
	this->ball_list[index].prev_position = this->ball_list[index].position;
	this->ball_list[index].position += vel;
	this->ball_list[index].acceleration = sf::Vector2f(0, 0);
}

void VerletSolver::update_positions(float deltaTime)
{
	for (uint32_t i = 0; i < this->ball_count; i++)
	{
		update_ball_position(i, deltaTime);
	}
}

void VerletSolver::apply_gravity()
{
	for (uint32_t i = 0; i < this->ball_count; i++)
	{
		this->ball_list[i].acceleration += this->gravity;
	}
}

void VerletSolver::apply_constraint()
{
	for (uint32_t i = 0; i < this->ball_count; i++)
	{
		sf::Vector2f vec = this->ball_list[i].position - conf::constraint_center;
		float sqr_dist = vec.x * vec.x + vec.y * vec.y;
		if (sqrt(sqr_dist) + conf::circle_radius > conf::constraint_radius)
		{
			sf::Vector2f norm = vec / sqrt(vec.x * vec.x + vec.y * vec.y);
			this->ball_list[i].position = conf::constraint_center + norm * (conf::constraint_radius - conf::circle_radius);
		}
	}
}
