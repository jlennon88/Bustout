#pragma once

#include "Shapes.h"

#include <optional>

namespace bustout
{
	bool testCollision_CircleCircle(
		  const Circle& circleA
		, const Circle& circleB
	) noexcept;

	// returns the nearest point on the paddle axis if there is a collision
	std::optional<sf::Vector2f> testCollision_CircleCapsule(
		  const Circle& circle
		, const Capsule& capsule
	) noexcept;

	bool testCollision_CircleRect(
		  const Circle & circle
		, const Rectangle & rect
	) noexcept;

	bool testCollision_CapsuleRect(
		  const Capsule& capsule
		, const Rectangle& rect
	) noexcept;

	bool testCollision_RectRect(
		  const Rectangle& rectA
		, const Rectangle& rectB
	) noexcept;

	Rectangle calculateAABB(const Circle& circle);
}