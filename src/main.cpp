#include <SFML/Graphics.hpp>

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

#include "game/collision.h"
#include "maths.h"
#include "gfx/AnimatedSprite.h"
#include "game/Paddle.h"
#include "ui/Button.h"
#include "ui/Canvas.h"

#include <iostream>

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 800;

const static sf::Vector2f SpaceScale = { 2 , -2 };

bool buttonState = false;
void onButtonClick()
{
	if (!buttonState)
	{
		std::cout << "Button Clicked\n";
		buttonState = true;
	}
}
void onButtonReleased()
{
	if (buttonState)
	{
		std::cout << "Button Released\n";
		buttonState = false;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout", sf::Style::Default & ~sf::Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	bustout::Canvas testCanvas(MainWindowWidth, MainWindowHeight);
	auto button = testCanvas.addElement<bustout::Button>(onButtonClick, onButtonReleased, "Button");

	sf::View uiView = window.getView();
	sf::View worldView = window.getView();
	worldView.setCenter(0.0f, 0.0f);
	worldView.setSize(SpaceScale);

	const sf::Color clearColor = { 0x55, 0x55, 0x55, 0xFF };

	bustout::Paddle paddle({ 0.0f, -0.9f });

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
		paddle.update(elapsedTime);

		// draw scene
		window.setView(worldView);

	/*	const auto mousePos = sf::Mouse::getPosition(window);
		ball.position = { ((float)mousePos.x - 0.5f * (float)MainWindowWidth) * (SpaceScale.x / (float)MainWindowWidth), ((float)mousePos.y - 0.5f * (float)MainWindowHeight) * (SpaceScale.y / (float)MainWindowHeight) };
		const auto collisionData = bustout::testCollision_BallPaddle(ball, paddle);
		if (collisionData.has_value())
		{
			bustout::DebugRenderer::get().setOutlineColour({ 0xFF, 0x00, 0x00, 0xFF });

			sf::Vertex linePoints[2] = {
				{ collisionData.value(), sf::Color::White, {} },
				{ ball.position, sf::Color::White, {} },
			};

			window.draw(linePoints, 2, sf::PrimitiveType::Lines);

			const auto contactPoint = paddle.radius * bustout::normalise(ball.position - collisionData.value()) + collisionData.value();

			bustout::DebugRenderer::get().draw(window);

			sf::CircleShape dot;
			dot.setRadius(0.005f);
			dot.setFillColor(sf::Color::White);
			dot.setOutlineColor({});
			dot.setPosition(contactPoint);
			dot.setOrigin({ 0.005f, 0.005f });
			window.draw(dot);
		}
		else
		{
			bustout::DebugRenderer::get().setOutlineColour({ 0x00, 0xFF, 0x00, 0xFF });

			bustout::DebugRenderer::get().draw(window);
		}*/

		paddle.draw(window);


#ifdef BUSTOUT_DEBUG
		bustout::DebugRenderer::get().draw(window);
#endif

		// draw ui
		window.setView(uiView);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			testCanvas.onClick();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			testCanvas.onRelease();
		testCanvas.draw(window);

		const auto mousePosi = sf::Mouse::getPosition(window);
		const sf::Vector2f mousePosf = { (float)mousePosi.x, (float)mousePosi.y };
		sf::CircleShape mouseDot;
		mouseDot.setPosition(mousePosf);
		mouseDot.setFillColor(sf::Color::White);
		mouseDot.setRadius(1.0f);
		mouseDot.setOrigin(0.5f, 0.5f);
		window.draw(mouseDot);

		window.display();
	}

	return 0;
}