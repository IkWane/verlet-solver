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
		solve_collisions();
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

uint32_t VerletSolver::get_ball_count()
{
	return this->ball_count;
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

void VerletSolver::solve_collisions()
{
	for (uint32_t i = 0; i < this->ball_count; i++)
	{
		for (uint32_t j = i + 1; j < this->ball_count; j++)
		{
			sf::Vector2f vec = this->ball_list[i].position - this->ball_list[j].position;
			float dist = sqrt(vec.x * vec.x + vec.y * vec.y) - conf::circle_radius * 2;
			if (dist < 0)
			{
				sf::Vector2f displacement = vec / (dist + conf::circle_radius * 2) * dist;
				this->ball_list[i].position -= 0.5f * displacement;
				this->ball_list[j].position += 0.5f * displacement;
			}
		}
	}
}
