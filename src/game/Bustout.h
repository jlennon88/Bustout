#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "BlockGrid.h"

namespace bustout
{
	class Bustout
	{
	public:
		Bustout();

		void update(float elapsedTime) noexcept;
		void draw(sf::RenderTarget& target);

	private:
		float m_ballSpeed = 1.0f;
		bool m_ballFixed = true;
		Ball m_ball;
		Paddle m_paddle;
		BlockGrid m_blockGrid;
	};
}