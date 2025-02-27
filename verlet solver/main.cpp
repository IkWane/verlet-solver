#include <SFML/Graphics.hpp>
#include <iostream>
#include "configuraton.hpp"
#include "VerletSolver.hpp"

sf::Color randomColor();
sf::Color hsv2rgb(float h, float s, float v);

int main() {
	sf::RenderWindow window(sf::VideoMode(conf::window_size.x, conf::window_size.y), "verlet solver");
	window.setFramerateLimit(conf::framerate);
	sf::CircleShape shape(.5f);
	shape.setFillColor(sf::Color::White);
	sf::Clock clock;
	float t = 0;
	VerletSolver simulation;

	sf::Vector2f previousMousePos{};

    float h{ 0 };

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

		sf::Vector2f mousePosition = (sf::Vector2f)(sf::Mouse::getPosition(window));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2f delta = mousePosition - previousMousePos;
			simulation.moveBalls(mousePosition, 20, delta);
		}
		previousMousePos = mousePosition;

		sf::Time deltaTime = clock.restart();

		if (t <= 0 && simulation.get_ball_count() < 10000)
		{
			for (int i = 0; i < 15; i++)
			{
				simulation.add_ball({ 150, 200 + (float)(6 * i) }, { 10 * conf::substeps * conf::substeps, 0 }, hsv2rgb(fmod(h, 360.f), 1.f, 1.f), 3);
                h += 0.05f;
			}
			t = 0.015f;
		} else {
			t -= conf::deltaTime;
		}

		simulation.update(conf::deltaTime, conf::substeps);

		window.clear({127, 127, 127, 255});
		shape.setFillColor(sf::Color::Black);
		shape.setOrigin({ conf::constraint_radius, conf::constraint_radius });
		shape.setPosition(conf::constraint_center);
		shape.setRadius(conf::constraint_radius);
		window.draw(shape);
		simulation.render(window, shape);
		window.display();
	}
}

sf::Color randomColor()
{
	return sf::Color((sf::Uint8)(rand() * 255), (sf::Uint8)(rand() * 255) , (sf::Uint8)(rand() * 255));
}

sf::Color hsv2rgb(float h, float s, float v)
{
	sf::Color RGB;
	float H = h, S = s, V = v,
		P, Q, T,
		fract;

	(H == 360.) ? (H = 0.) : (H /= 60.);
	fract = H - floor(H);

	P = V * (1. - S);
	Q = V * (1. - S * fract);
	T = V * (1. - S * (1. - fract));

	if (0. <= H && H < 1.)
		RGB = { static_cast<sf::Uint8>(V * 255), static_cast<sf::Uint8>(T * 255), static_cast<sf::Uint8>(P * 255) };
	else if (1. <= H && H < 2.)
		RGB = { static_cast<sf::Uint8>(Q * 255), static_cast<sf::Uint8>(V * 255), static_cast<sf::Uint8>(P * 255) };
	else if (2. <= H && H < 3.)
		RGB = { static_cast<sf::Uint8>(P * 255), static_cast<sf::Uint8>(V * 255), static_cast<sf::Uint8>(T * 255) };
	else if (3. <= H && H < 4.)
		RGB = { static_cast<sf::Uint8>(P * 255), static_cast<sf::Uint8>(Q * 255), static_cast<sf::Uint8>(V * 255) };
	else if (4. <= H && H < 5.)
		RGB = { static_cast<sf::Uint8>(T * 255), static_cast<sf::Uint8>(P * 255), static_cast<sf::Uint8>(V * 255) };
	else if (5. <= H && H < 6.)
		RGB = { static_cast<sf::Uint8>(V * 255), static_cast<sf::Uint8>(P * 255), static_cast<sf::Uint8>(Q * 255) };
	else
		RGB = { 0, 0, 0 };

	return RGB;
}