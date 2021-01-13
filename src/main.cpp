#include <SFML/Graphics.hpp>

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

#include "game/collision.h"
#include "maths.h"
#include "gfx/AnimatedSprite.h"
#include "game/Bustout.h"
#include "ui/Text.h"

#include <sstream>
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

	bustout::Rectangle rect;
	rect.topLeft = { -0.7f, 0.7f };
	rect.widthHeight = { 0.1f, 0.1f };

	const float mouseCircleRad = 0.05f;
	bustout::Circle mouseCircle;
	mouseCircle.radius = mouseCircleRad;
	
	bustout::DebugRenderer::get().registerObject(rect);
	bustout::DebugRenderer::get().registerObject(mouseCircle);

	auto gameInstance = std::make_unique<bustout::Bustout>();

	bustout::Text scoreText("Score: 0");
	bustout::Text livesText("Lives: 0");

	int prevScore = 0;
	int prevLives = 0;

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
		gameInstance->update(elapsedTime);
		if (gameInstance->getScore() != prevScore)
		{
			prevScore = gameInstance->getScore();
			std::stringstream ss;
			ss << "Score: " << prevScore;
			scoreText.setText(ss.str());
		}
		if (gameInstance->getLives() != prevLives)
		{
			if (gameInstance->getLives() == 0)
			{
				// game over, just restart
				gameInstance = std::make_unique<bustout::Bustout>();
				continue;
			}
			prevLives = gameInstance->getLives();
			std::stringstream ss;
			ss << "Lives: " << prevLives;
			livesText.setText(ss.str());
			const auto extent = livesText.getExtent();
			livesText.setPosition({ (float)MainWindowWidth - extent.x, 0.0f });
		}

		// draw scene
		window.setView(worldView);


		gameInstance->draw(window);

#ifdef BUSTOUT_DEBUG
		// some debug-specific tests
		const auto mousePosi = sf::Mouse::getPosition(window);
		const sf::Vector2f mousePosf = { (float)(mousePosi.x - MainWindowWidth / 2), (float)(mousePosi.y - MainWindowHeight / 2) };
		const sf::Vector2f mousePosScaled = { mousePosf.x * 2 / (float)MainWindowWidth, -mousePosf.y * 2 / (float)MainWindowHeight };

		mouseCircle.position = mousePosScaled;
		sf::CircleShape mouseDot;
		mouseDot.setPosition(mousePosScaled);
		mouseDot.setFillColor(sf::Color::White);
		mouseDot.setRadius(mouseCircleRad);
		mouseDot.setOrigin(mouseCircleRad, mouseCircleRad);
		window.draw(mouseDot);

		bustout::DebugRenderer::get().draw(window);
		bustout::debugCircleRectCollision(window, mouseCircle, rect);
#endif

		// draw ui
		window.setView(uiView);

		scoreText.draw(window);
		livesText.draw(window);

		window.display();
	}

	return 0;
}