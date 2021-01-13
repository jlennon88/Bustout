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

	std::optional<sf::Vector2f> testCollision_CircleRect(
		  const Circle& circle
		, const Rectangle& rect
	) noexcept
	{
		const auto rectMidpoint = rect.topLeft + sf::Vector2f{ 0.5f * rect.widthHeight.x, -0.5f * rect.widthHeight.y };

		// vector from centre of circle to rectangle
		const auto circleRectVector = rectMidpoint - circle.position;

		const float circleRectDist = length(circleRectVector);
		const auto nearestPoint = circleRectVector * (1 / circleRectDist) * clamp(circle.radius, 0.0f, circleRectDist) + circle.position;

		if (isZero(circleRectDist) || testCollision_PointRect(nearestPoint, rect))
			return { nearestPoint };
		return {};
	}

	bool testCollision_PointRect(const sf::Vector2f& point, const Rectangle& rect) noexcept
	{
		const bool isLeft = point.x < rect.topLeft.x;
		const bool isRight = point.x > rect.topLeft.x + rect.widthHeight.x;
		const bool isAbove = point.y > rect.topLeft.y;
		const bool isBelow = point.y < rect.topLeft.y - rect.widthHeight.y;

		return !(isLeft || isRight || isAbove || isBelow);
	}

	bool testCollision_CapsuleRect(
		  const Capsule& capsule
		, const Rectangle& rect
	) noexcept
	{
		return false;
	}

	bool testCollision_RectRect(const Rectangle& rectA, const Rectangle& rectB) noexcept
	{
		const bool isLeft = rectA.topLeft.x + rectA.widthHeight.x < rectB.topLeft.x;
		const bool isRight = rectA.topLeft.x > rectB.topLeft.x + rectB.widthHeight.x;
		const bool isAbove = rectA.topLeft.y - rectA.widthHeight.y > rectB.topLeft.y;
		const bool isBelow = rectA.topLeft.y < rectB.topLeft.y - rectB.widthHeight.y;

		return !(isLeft || isRight || isAbove || isBelow);
	}

	bool testCollision_LineLine(const Line& lineA, const Line& lineB) noexcept
	{
		const auto r = lineA.p1 - lineA.p0;
		const auto s = lineB.p1 - lineB.p0;
		const auto deltaP0 = lineB.p0 - lineA.p0;

		const float rxs = cross(r, s);
		const float t = cross(deltaP0, s) / rxs;
		const float u = cross(deltaP0, r) / rxs;

		return !isZero(rxs) && (0.0f <= t) && (t <= 1.0f) && (0.0f <= u) && (u <= 1.0f);
	}

	Rectangle calculateAABB(const Circle& circle)
	{
		Rectangle aabb;
		aabb.topLeft = { circle.position.x - circle.radius, circle.position.y + circle.radius };
		aabb.widthHeight = { 2.0f * circle.radius, 2.0f * circle.radius };
		return aabb;
	}
}