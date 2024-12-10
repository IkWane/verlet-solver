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
	float t = 0;

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

		if (t <= 0 && simulation.get_ball_count() < 1000)
		{
			simulation.add_ball({ 500, 100 }, { 0, 200000 });
			simulation.add_ball({ 510, 100 }, { 0, 200000 });
			t = 0.03f;
		} else {
			t -= deltaTime.asSeconds();
		}

		simulation.update(deltaTime.asSeconds(), conf::substeps);

		window.clear();
		simulation.render(&window, &shape);
		window.display();
	}
}