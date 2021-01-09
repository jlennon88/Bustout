#include <SFML/Graphics.hpp>

#include "DebugDraw.h"

#include "collision.h"
#include "maths.h"
#include "Sprite.h"

#include <iostream>

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 600;

const static sf::Vector2f SpaceScale = { 2 , -2 * (float)MainWindowHeight / (float)MainWindowWidth };

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout");
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	sf::View uiView = window.getView();
	sf::View worldView = window.getView();
	worldView.setCenter(0.0f, 0.0f);
	worldView.setSize(SpaceScale);

	bustout::Ball ball;
	ball.position = { 0.0f, 0.0f };
	ball.velocity = { 0.0f, 0.0f };
	ball.radius = 0.02f;
	bustout::DebugRenderer::get().registerObject(ball);

	const float paddleSpeed = 0.5f;
	bustout::Paddle paddle;
	paddle.pointA = { -0.075f, -0.5f };
	paddle.pointB = {  0.075f, -0.5f };
	paddle.radius = 0.02f;
	bustout::DebugRenderer::get().registerObject(paddle);

	const sf::Color clearColor = { 0x55, 0x55, 0x55, 0xFF };

	bustout::Sprite paddleSprite("paddle_beam.png");
	paddleSprite.setTextureRect({ 0, 0, 128, 24 });
	paddleSprite.setScale({ 0.15f / 128.0f, 0.15f / 128.0f });

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

		const auto mousePos = sf::Mouse::getPosition(window);
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
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			paddle.pointA.x -= paddleSpeed * (1 / 75.0f);
			paddle.pointB.x -= paddleSpeed * (1 / 75.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			paddle.pointA.x += paddleSpeed * (1 / 75.0f);
			paddle.pointB.x += paddleSpeed * (1 / 75.0f);
		}
		const float paddleLength = bustout::length(paddle.pointB - paddle.pointA);
		paddle.pointA.x = bustout::clamp(paddle.pointA.x, -1.0f + paddle.radius, 1.0f - paddle.radius - paddleLength);
		paddle.pointB.x = bustout::clamp(paddle.pointB.x, -1.0f + paddle.radius + paddleLength, 1.0f - paddle.radius);

		paddleSprite.draw(window, 0.5f * (paddle.pointB + paddle.pointA));

		// draw ui
		window.setView(uiView);
		
		window.display();
	}

	bustout::DebugRenderer::get().removeObject(ball);
	bustout::DebugRenderer::get().removeObject(paddle);

	return 0;
}