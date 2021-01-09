#include "collision.h"

#include "maths.h"

namespace bustout
{
	bool testCollision_CircleCircle(
		  const Circle& circleA
		, const Circle& circleB
	) noexcept
	{
		const auto delta = circleA.position - circleB.position;
		const float d2 = dot(delta, delta);
		const float sr = circleA.radius + circleB.radius;
		const float sr2 = sr * sr;
		return sr2 > d2;
	}

	std::optional<sf::Vector2f> testCollision_CircleCapsule(
		  const Circle& circle
		, const Capsule& capsule
	) noexcept
	{
		const auto capsulePointA = capsule.position - sf::Vector2f(capsule.halfLength, 0.0f);
		const auto capsuleVector = sf::Vector2f(2 * capsule.halfLength, 0.0f);
		const auto circleVector = circle.position - capsulePointA;

		const float capsuleLength = length(capsuleVector);
		const float circleLength = length(circleVector);

		const float overlap = clamp(dot(capsuleVector, circleVector) * (1 / capsuleLength), 0.0f, capsuleLength);

		const auto point = overlap * (capsuleVector * (1 / capsuleLength));

		const float d2 = length2(circleVector - point);

		const float radSum = circle.radius + capsule.radius;
		const float radSum2 = radSum * radSum;
		if (radSum2 > d2)
			return { point + capsulePointA };
		else
			return {};
	}

	bool testCollision_CircleRect(
		  const Circle& circle
		, const Rectangle& rect
	) noexcept
	{
		return false;
	}


	bool testCollision_CapsuleRect(
		  const Capsule& capsule
		, const Rectangle& rect
	) noexcept
	{
		return false;
	}
}