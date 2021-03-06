#include "Bustout.h"

#include "maths.h"
#include "collision.h"

namespace bustout
{
	Bustout::Bustout()
		: m_paddle({ 0.0f, -0.8f })
		, m_blockGrid(10, 10)
	{
		m_killzone.topLeft = { -1.0f, -1.0f };
		m_killzone.widthHeight = { 2.0f, 0.1f };
	}

	void Bustout::update(float elapsedTime) noexcept
	{
		// TODO: might make this depend on the ball speed, to prevent it from passing through objects at higher speeds
		constexpr int UpdateIterations = 8;
		static_assert(UpdateIterations > 0);
		const float subElapedTime = elapsedTime / static_cast<float>(UpdateIterations);
		
		for (int i = 0; i < UpdateIterations; ++i)
		{
			m_paddle.update(subElapedTime);
			if (!m_ballFixed)
			{
				m_ball.update(subElapedTime);

				// the following assumes that the ball can't interact with the paddle, killzone
				// and block grid on the same iteration, so it depends on the speed of the ball
				
				if (m_ball.getPosition().y < m_killzone.topLeft.y + m_killzone.widthHeight.y)
				{
					// if the ball is below the top of the killzone, then lose a life
					--m_lives;
					m_ballFixed = true;
					if (m_lives == 0)
					{
						// TODO: implement 'game over'
					}
				}
				else if (testCollision_RectRect(m_ball.getAABB(), m_paddle.getAABB()))
				{
					auto collisionData = testCollision_CircleCapsule(m_ball.getShape(), m_paddle.getShape());
					if (collisionData.has_value())
					{
						const auto disp = m_ball.getPosition() - collisionData.value();
						const float dist = m_paddle.getShape().radius + m_ball.getShape().radius - length(disp);
						const auto norm = normalise(disp);
						m_ball.setPosition(m_ball.getPosition() + norm * dist);

						const sf::Vector2f paddleVelocity = (m_paddle.getPosition() - m_paddle.getPrevPosition()) / subElapedTime;
						m_ball.setVelocity(normalise(reflect(m_ball.getVelocity(), norm) + paddleVelocity) * m_ballSpeed);
					}
				}
				else if(m_blockGrid.handleCollision(m_ball))
				{
					m_score += m_scoreIncrement;
					if (m_blockGrid.getRemainingBlocks() == 0)
					{
						// TODO: implement 'game won'
					}
				}
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					// release the ball and add the velocity direction of the paddle to give some
					// control over the initial trajectory
					const sf::Vector2f paddleVelocity = (m_paddle.getPosition() - m_paddle.getPrevPosition()) / subElapedTime;
					m_ball.setVelocity(normalise(sf::Vector2f(1, 1) + paddleVelocity) * m_ballSpeed);
					m_ballFixed = false;
				}
				else
				{
					// ball is 'stuck' to the paddle by a simple offset
					const auto ballPosition = m_paddle.getPosition() + sf::Vector2f(0.0f, m_paddle.getShape().radius + m_ball.getShape().radius);
					m_ball.setPosition(ballPosition);
				}
			}
		}
	}
	void Bustout::draw(sf::RenderTarget& target)
	{
		auto killzoneColour = sf::Color::Red;
		killzoneColour.a = 255 / 2;
		sf::RectangleShape killzoneGfx;
		killzoneGfx.setFillColor(killzoneColour);
		killzoneGfx.setPosition(m_killzone.topLeft);
		killzoneGfx.setSize(m_killzone.widthHeight);
		target.draw(killzoneGfx);

		m_blockGrid.draw(target);
		m_paddle.draw(target);
		m_ball.draw(target);
	}
	bool Bustout::isGameOver() const noexcept
	{
		return m_lives == 0 || m_blockGrid.getRemainingBlocks() <= 0;
	}
}
