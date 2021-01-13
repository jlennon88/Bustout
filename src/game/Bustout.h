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

		const BlockGrid& getBlockGrid() const noexcept { return m_blockGrid; }

		int getScore() const noexcept { return m_score; }
	private:
		float m_ballSpeed = 1.0f;
		bool m_ballFixed = true;
		int m_score = 0;
		int m_scoreIncrement = 100;
		Ball m_ball;
		Paddle m_paddle;
		BlockGrid m_blockGrid;
		Rectangle m_killzone;
	};
}