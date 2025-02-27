#include "CollisionGrid.hpp"
#include <iostream>

CollisionGrid::CollisionGrid(sf::Vector2u gridPixelSize, sf::Vector2u gridSize) : gridPixelSize(gridPixelSize), gridSize(gridSize)
{
	cells.resize(gridSize.x * gridSize.y);
}

void CollisionGrid::updateGrid(std::vector<Ball>& elements)
{
	sf::Vector2f ratio = { static_cast<float>(gridPixelSize.x / gridSize.x), static_cast<float>(gridPixelSize.y / gridSize.y) };
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i].clear();
	}
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		int gridIndex = getCellIndex({ (int)floor(elements[i].position.x / ratio.x), (int)floor(elements[i].position.y / ratio.y) });
		if (gridIndex < cells.size())
		{
			cells[gridIndex].push_back(i);
		}
	}
}

sf::Vector2u CollisionGrid::getGridSize()
{
	return gridSize;
}

std::vector<int>& CollisionGrid::getElementsAt(sf::Vector2i position)
{
	return cells[getCellIndex(position)];
}

int* CollisionGrid::getNeighbors(sf::Vector2i position)
{
	int* neighbors = new int[9];
	int index = 0;
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
				neighbors[i * 3 + j] = getCellIndex(position + sf::Vector2i{ j - 1, i - 1 });
		}
	}
	return neighbors;
}

std::vector<int>& CollisionGrid::getElements(int index)
{
	return cells[index];
}

int CollisionGrid::getCellIndex(sf::Vector2i position)
{
	if (position.x >= 0 && position.x < gridSize.x && position.y >= 0 && position.y < gridSize.y)
	{
		return position.x + position.y * gridSize.x;
	}
	return -1;
}
