#include <SFML/Graphics.hpp>

#include "DebugDraw.h"

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 600;

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout");
	window.setVerticalSyncEnabled(true);

	sf::View uiView = window.getView();
	sf::View worldView = window.getView();
	worldView.setCenter(0.0f, 0.0f);
	worldView.setSize(
		{
			 static_cast<float>(MainWindowWidth),
			-static_cast<float>(MainWindowHeight),
		}
	);

	bustout::Ball ball;
	ball.radius = 20.0f;
	ball.position = { 0.0f, 0.0f };
	ball.velocity = { 0.0f, 0.0f };
	bustout::DebugRenderer::get().registerObject(ball);

	const sf::Color clearColor = { 0x55, 0x55, 0x55, 0xFF };

	bool shouldClose = false;
	while (!shouldClose)
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
				shouldClose = true;
		}

		window.clear(clearColor);

		// draw scene
		window.setView(worldView);

		// draw ui
		window.setView(uiView);

		const auto mousePos = sf::Mouse::getPosition(window);
		ball.position = { (float)mousePos.x, (float)mousePos.y };
		bustout::DebugRenderer::get().draw(window);
		
		window.display();
	}

	bustout::DebugRenderer::get().removeObject(ball);

	return 0;
}