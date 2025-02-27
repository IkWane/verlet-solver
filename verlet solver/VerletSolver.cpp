#include "VerletSolver.hpp"
#include <iostream>
#include <math.h>

VerletSolver::VerletSolver() : collisionGrid(conf::window_size, conf::grid_size) {}

void VerletSolver::add_ball(sf::Vector2f pos, sf::Vector2f accel, sf::Color color, float radius)
{
	ball_list.push_back({ pos, pos, accel, color, radius, true });
	ball_count++;
}

void VerletSolver::update(float deltaTime, uint8_t substeps)
{
	for (uint8_t i = 0; i < substeps; i++)
	{
		apply_gravity();
		collisionGrid.updateGrid(ball_list);
		solve_collisions();
		update_positions(deltaTime / substeps);
		apply_constraint();
	}
	release_hold();
}

void VerletSolver::render(sf::RenderWindow& window, sf::CircleShape& ball_shape)
{
	for (auto& ball : this->ball_list)
	{
		ball_shape.setOrigin(ball.radius, ball.radius);
		ball_shape.setPosition(ball.position);
		ball_shape.setRadius(ball.radius);
		ball_shape.setFillColor(ball.color);
		window.draw(ball_shape);
	}
}

uint32_t VerletSolver::get_ball_count()
{
	return this->ball_count;
}

void VerletSolver::moveBalls(sf::Vector2f attractionCenter, float radius, sf::Vector2f delta)
{
	for (uint32_t i = 0; i < this->ball_count; i++)
	{
		float X = attractionCenter.x - ball_list[i].position.x;
		float Y = attractionCenter.y - ball_list[i].position.y;
		float dist = sqrt(X * X + Y * Y);
		if (dist <= radius) {
			ball_list[i].position += delta;
			ball_list[i].positionUpdate = false;
		}
	}
}

void VerletSolver::remove_ball(uint32_t index)
{
	this->ball_list.erase(ball_list.begin() + index);
	this->ball_count--;
}

void VerletSolver::update_ball_position(uint32_t index, float deltaTime)
{
	if (ball_list[index].positionUpdate)
	{
		sf::Vector2f vel = this->ball_list[index].position - this->ball_list[index].prev_position;
		vel += this->ball_list[index].acceleration * deltaTime;
		this->ball_list[index].prev_position = this->ball_list[index].position;
		this->ball_list[index].position += vel;
		this->ball_list[index].acceleration = sf::Vector2f(0, 0);
	}
	else {
		this->ball_list[index].prev_position = this->ball_list[index].position;
		this->ball_list[index].acceleration = sf::Vector2f(0, 0);
	}
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
		if (sqrt(sqr_dist) + this->ball_list[i].radius > conf::constraint_radius)
		{
			sf::Vector2f norm = vec / sqrt(vec.x * vec.x + vec.y * vec.y);
			this->ball_list[i].position = conf::constraint_center + norm * (conf::constraint_radius - this->ball_list[i].radius);
		}
	}
}

void VerletSolver::solve_collisions()
{
	for (int y = 0; y < collisionGrid.getGridSize().y; y++)
	{
		for (int x = 0; x < collisionGrid.getGridSize().x; x++)
		{
			int* neighbors = collisionGrid.getNeighbors({ x, y });
			std::vector<int>& inCell = collisionGrid.getElementsAt({ x, y });
			for (int n = 0; n <= 8; n++)
			{
				if (neighbors[n] >= 0)
				{
					for (int i = 0; i < inCell.size(); i++)
					{
						std::vector<int>& inNeighborCell = collisionGrid.getElements(neighbors[n]);
						for (int j = 0; j < inNeighborCell.size(); j++)
						{
							if (inCell[i] != inNeighborCell[j])
							{
								sf::Vector2f vec = ball_list[inCell[i]].position - ball_list[inNeighborCell[j]].position;
								float dist = sqrt(vec.x * vec.x + vec.y * vec.y) - (ball_list[inCell[i]].radius + ball_list[inNeighborCell[j]].radius);
								if (dist < 0)
								{
									sf::Vector2f displacement = vec / (dist + ball_list[inCell[i]].radius + ball_list[inNeighborCell[j]].radius) * dist;
									ball_list[inCell[i]].position -= 0.5f * displacement;
									ball_list[inNeighborCell[j]].position += 0.5f * displacement;
								}
							}
						}
					}
				}
			}
			delete[] neighbors;
		}
	}
}

void VerletSolver::solve_collisions_soft()
{
	for (uint32_t i = 0; i < this->ball_count; i++)
	{
		for (uint32_t j = i + 1; j < this->ball_count; j++)
		{
			sf::Vector2f vec = this->ball_list[i].position - this->ball_list[j].position;
			float dist = sqrt(vec.x * vec.x + vec.y * vec.y) - (this->ball_list[i].radius + this->ball_list[j].radius);
			if (dist < 0)
			{
				sf::Vector2f displacement = vec / (dist + this->ball_list[i].radius + this->ball_list[j].radius) * dist;
				this->ball_list[i].position -= conf::soft_collision_factor * displacement;
				this->ball_list[j].position += conf::soft_collision_factor * displacement;
			}
		}
	}
}

void VerletSolver::release_hold()
{
	for (int i = 0; i < ball_count; i++)
	{
		ball_list[i].positionUpdate = true;
	}
}
