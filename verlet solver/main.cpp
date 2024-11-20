#include <SFML/Graphics.hpp>
#include "configuraton.hpp"
#include "VerletSolver.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(conf::window_size.x, conf::window_size.y), "verlet solver");
	window.setFramerateLimit(conf::framerate);
	sf::CircleShape shape(conf::circle_radius);
	shape.setOrigin(conf::circle_radius, conf::circle_radius);
	shape.setFillColor(sf::Color::White);
	sf::Clock clock;

	VerletSolver simulation;

	while (window.isOpen())	
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		sf::Time deltaTime = clock.restart();
		simulation.add_ball({ 500, 100 }, { 0, 0 });
		simulation.update(deltaTime.asSeconds(), conf::substeps);

		window.clear();
		simulation.render(&window, &shape);
		window.display();
	}
}