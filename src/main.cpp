#include <SFML/Graphics.hpp>

#ifdef BUSTOUT_DEBUG
#include "DebugDraw.h"
#endif

#include "collision.h"
#include "maths.h"
#include "AnimatedSprite.h"
#include "Paddle.h"

#include <iostream>

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 800;

const static sf::Vector2f SpaceScale = { 2 , -2 };
//
//constexpr float UIWidth = 0.2f;
//
//void onWindowResize(sf::RenderWindow& window, sf::View& worldView, sf::View& uiView)
//{
//	const float aspectRatio = window.getSize().y / static_cast<float>(window.getSize().x);
//	sf::FloatRect worldViewport{};
//	sf::FloatRect uiViewport{};
//	if (aspectRatio < 1)
//	{
//		worldViewport.width = (1.0f - UIWidth) * aspectRatio;
//		worldViewport.height = 1.0f;
//
//		uiViewport.left = worldViewport.width;
//		uiViewport.width = UIWidth * aspectRatio;
//		uiViewport.height = 1.0f;
//	}
//	else
//	{
//		worldViewport.width = 1.0f - UIWidth;
//		worldViewport.height = 1 / aspectRatio;
//
//		uiViewport.left = worldViewport.width;
//		uiViewport.width = UIWidth;
//		uiViewport.height = 1 / aspectRatio;
//	}
//	worldView.setViewport(worldViewport);
//	uiView.setViewport(uiViewport);
//}

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout", sf::Style::Default & ~sf::Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	sf::View uiView = window.getView();
	sf::View worldView = window.getView();
	worldView.setCenter(0.0f, 0.0f);
	worldView.setSize(SpaceScale);
//	onWindowResize(window, worldView, uiView);

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

		window.display();
	}

	return 0;
}