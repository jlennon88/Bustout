#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#pragma warning(pop)

#include "DebugDraw.h"

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 600;

void createCircleGrid(b2World& physicsWorld, float radius = 10.0f, float spacing = 2.0f)
{
	const int yCount = 10;
	const int xCount = 20;

	const float xInit = -0.5f * (2 * radius * xCount + spacing * (xCount - 1));
	const float step = 2 * radius + spacing;

	float yPos = -0.5f * (2 * radius * yCount + spacing * (yCount - 1));
	for (int y = 0; y < yCount; ++y)
	{
		float xPos = xInit + ((y % 2 == 0) ? step * 0.5f : 0.0f);
		for (int x = 0; x < xCount; ++x)
		{
			b2BodyDef circleBodyDef;
			circleBodyDef.position.Set(xPos, yPos);
			circleBodyDef.type = b2_dynamicBody;
			b2Body* circleBody = physicsWorld.CreateBody(&circleBodyDef);

			b2CircleShape circle;
			circle.m_radius = radius;
			circleBody->CreateFixture(&circle, 10.0f);

			xPos += step;
		}
		yPos += step;
	}
}

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

	// setup debug draw
	DebugDraw physicsDebugDraw(window);
	physicsDebugDraw.SetFlags(0x1F);

	b2World physicsWorld({ 0.0f, -9.81f });
	physicsWorld.SetDebugDraw(&physicsDebugDraw);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -250.0f);
	b2Body* groundBody = physicsWorld.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(static_cast<float>(MainWindowWidth), 50.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	createCircleGrid(physicsWorld);

	const sf::Color clearColor = { 0x55, 0x55, 0x55, 0xFF };

	const int32_t velocityIterations = 6;
	const int32_t positionIterations = 2;

	bool shouldClose = false;
	while (!shouldClose)
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
				shouldClose = true;
		}

		// update physics
		physicsWorld.Step(1 / 60.0f, velocityIterations, positionIterations);

		// draw scene
		window.clear(clearColor);

		window.setView(worldView);
		
		physicsWorld.DebugDraw();

		window.setView(uiView);
		// draw ui

		const auto mousePos = sf::Mouse::getPosition(window);
		
		window.display();
	}

	return 0;
}