#pragma once

#include <SFML/Graphics.hpp>

namespace bustout
{
	struct Circle
	{
		sf::Vector2f position;
		float radius;
	};

	struct Capsule
	{
		sf::Vector2f position;
		float halfLength;
		float radius;
	};

	struct Rectangle
	{
		sf::Vector2f topLeft;
		sf::Vector2f widthHeight;
	};
}