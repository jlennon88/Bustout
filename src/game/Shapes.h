#pragma once

#include <SFML/Graphics.hpp>

#include <array>

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

	struct Line
	{
		sf::Vector2f p0;
		sf::Vector2f p1;
	};

	inline std::array<Line, 4> getEdges(const Rectangle& rect) noexcept
	{
		const auto p00 = rect.topLeft;
		const auto p01 = rect.topLeft + sf::Vector2f(rect.widthHeight.x, 0.0f);
		const auto p10 = rect.topLeft + sf::Vector2f(0.0f, -rect.widthHeight.y);
		const auto p11 = rect.topLeft + sf::Vector2f(rect.widthHeight.x, -rect.widthHeight.y);

		return std::array<Line, 4>{
			Line{ p00, p01 },
			Line{ p01, p11 },
			Line{ p11, p10 },
			Line{ p10, p00 },
		};
	}
}