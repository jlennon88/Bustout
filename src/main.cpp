#include <SFML/Graphics.hpp>

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

#include "game/collision.h"
#include "maths.h"
#include "gfx/AnimatedSprite.h"
#include "game/Bustout.h"

#include <iostream>

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 800;

const static sf::Vector2f SpaceScale = { 2 , -2 };

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout", sf::Style::Default & ~sf::Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	sf::View uiView = window.getView();
	sf::View worldView = window.getView();
	worldView.setCenter(0.0f, 0.0f);
	worldView.setSize(SpaceScale);

	const sf::Color clearColor = { 0x55, 0x55, 0x55, 0xFF };

	bustout::Bustout gameInstance;

	sf::Clock clock;
	bool shouldClose = false;
	while (!shouldClose)
	{
		const float elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
				shouldClose = true;
		}

		window.clear(clearColor);

		// update scene
		gameInstance.update(elapsedTime);

		// draw scene
		window.setView(worldView);

		gameInstance.draw(window);


#ifdef BUSTOUT_DEBUG
		bustout::DebugRenderer::get().draw(window);
#endif

		// draw ui
		window.setView(uiView);

		const auto mousePosi = sf::Mouse::getPosition(window);
		const sf::Vector2f mousePosf = { (float)mousePosi.x, (float)mousePosi.y };
		sf::CircleShape mouseDot;
		mouseDot.setPosition(mousePosf);
		mouseDot.setFillColor(sf::Color::White);
		mouseDot.setRadius(3.0f);
		mouseDot.setOrigin(1.5f, 1.5f);
		window.draw(mouseDot);

		window.display();
	}

	return 0;
}