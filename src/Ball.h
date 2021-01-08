#pragma once

#include <SFML/System.hpp>

namespace bustout
{
	struct Ball
	{
		sf::Vector2f position;
		sf::Vector2f velocity;
		float radius;
	};
}
