#include <SFML/Graphics.hpp>
#include "configuraton.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(conf::window_size.x, conf::window_size.y), "verlet solver");
	window.setFramerateLimit(conf::framerate);
	sf::CircleShape shape(conf::circle_radius);
	shape.setOrigin(conf::circle_radius, conf::circle_radius);

	while (window.isOpen())	
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				
			}
		}
	}
}