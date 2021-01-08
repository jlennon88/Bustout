#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "PowerUp.h"

bool testCollision_BallBall(
	  const Ball& ballA
	, const Ball& ballB
) noexcept;

bool testCollision_BallPaddle(
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
