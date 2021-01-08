#include "collision.h"

#include "maths.h"

namespace bustout
{
	bool testCollision_BallBall(const Ball& ballA, const Ball& ballB) noexcept
	{
		const auto delta = ballA.position - ballB.position;
		const float d2 = dot(delta, delta);
		const float sr = ballA.radius + ballB.radius;
		const float sr2 = sr * sr;
		return sr2 > d2;
	}

	std::optional<sf::Vector2f> testCollision_BallPaddle(const Ball& ball, const Paddle& paddle) noexcept
	{
		const auto paddleVector = paddle.pointB - paddle.pointA;
		const auto ballVector = ball.position - paddle.pointA;

		const float paddleLength = length(paddleVector);
		const float ballLength = length(ballVector);

		const float overlap = clamp(dot(paddleVector, ballVector) * (1 / paddleLength), 0.0f, paddleLength);

		const auto point = overlap * (paddleVector * (1 / paddleLength));

		const float d2 = length2(ballVector - point);

		const float radSum = ball.radius + paddle.radius;
		const float radSum2 = radSum * radSum;
		if (radSum2 > d2)
			return { point + paddle.pointA };
		else
			return {};
	}

	bool testCollision_BallBlock(const Ball& ball, const Block& block) noexcept
	{
		return false;
	}

	bool testCollision_PaddlePowerUp(const Paddle& paddle, const PowerUp& powerUp) noexcept
	{
		return false;
	}
}