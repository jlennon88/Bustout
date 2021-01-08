#include "collision.h"

constexpr float dot(const sf::Vector2f& u, const sf::Vector2f& v) noexcept
{
	return u.x * v.x + u.y * v.y;
}

bool testCollision_BallBall(const Ball& ballA, const Ball& ballB) noexcept
{
	const auto delta = ballA.position - ballB.position;
	const float d2 = dot(delta, delta);
	const float sr = ballA.radius + ballB.radius;
	const float sr2 = sr * sr;
	return sr2 > d2;
}
