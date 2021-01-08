#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "PowerUp.h"

#include <optional>

namespace bustout
{
	bool testCollision_BallBall(
		  const Ball& ballA
		, const Ball& ballB
	) noexcept;

	// returns the contact point on the paddle if there is a collision
	std::optional<sf::Vector2f> testCollision_BallPaddle(
		  const Ball& ball
		, const Paddle& paddle
	) noexcept;

	bool testCollision_BallBlock(
		  const Ball& ball
		, const Block& block
	) noexcept;

	bool testCollision_PaddlePowerUp(
		  const Paddle& paddle
		, const PowerUp& powerUp
	) noexcept;
}