#pragma once

#include <SFML/System.hpp>

namespace bustout
{
	// the paddle is represented by a 2D capsule
	struct Paddle
	{
		// 'start' vertex of the capsule
		sf::Vector2f pointA;
		// 'end' vertex of the capsule
		sf::Vector2f pointB;

		float radius;
	};
}