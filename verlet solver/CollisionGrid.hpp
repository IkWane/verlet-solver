#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "ball.hpp"

class CollisionGrid
{
public:
	CollisionGrid(sf::Vector2u gridPixelSize, sf::Vector2u gridSize);
	void updateGrid(std::vector<Ball>& elements);
	sf::Vector2u getGridSize();
	std::vector<int>& getElementsAt(sf::Vector2i position);
	int* getNeighbors(sf::Vector2i position);
	std::vector<int>& getElements(int index);

private:
	int getCellIndex(sf::Vector2i pos);

	sf::Vector2u gridSize;
	sf::Vector2u gridPixelSize;
	std::vector<std::vector<int>> cells;
};

