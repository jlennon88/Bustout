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

	bool testCollision_BallPaddle(const Ball& ball, const Paddle& paddle) noexcept
	{
		return false;
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