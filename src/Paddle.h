#pragma once

#include <SFML/System.hpp>

namespace bustout
{
	// the paddle is represented by a 2D capsule
	struct Paddle
	{
		sf::Vector2f position;
		float length;
		float radius;
	};
}