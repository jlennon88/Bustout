#include "Bustout.h"

#include "maths.h"
#include "collision.h"

namespace bustout
{
	Bustout::Bustout()
		: m_paddle({ 0.0f, -0.8f })
		, m_blockGrid(10, 10)
	{
	}

	void Bustout::update(float elapsedTime) noexcept
	{
		constexpr int UpdateIterations = 8;
		static_assert(UpdateIterations > 0);
		const float subElapedTime = elapsedTime / static_cast<float>(UpdateIterations);
		
		for (int i = 0; i < UpdateIterations; ++i)
		{
			m_paddle.update(subElapedTime);
			if (!m_ballFixed)
			{
				m_ball.update(subElapedTime);
				if (testCollision_RectRect(m_ball.getAABB(), m_paddle.getAABB()))
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
				else
				{
					m_blockGrid.handleCollision(m_ball);
				}
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					const sf::Vector2f paddleVelocity = (m_paddle.getPosition() - m_paddle.getPrevPosition()) / subElapedTime;
					m_ball.setVelocity(normalise(sf::Vector2f(1, 1) + paddleVelocity) * m_ballSpeed);
					m_ballFixed = false;
				}
				else
				{
					const auto ballPosition = m_paddle.getPosition() + sf::Vector2f(0.0f, m_paddle.getShape().radius + m_ball.getShape().radius);
					m_ball.setPosition(ballPosition);
				}
			}
		}
	}
	void Bustout::draw(sf::RenderTarget& target)
	{
		m_blockGrid.draw(target);
		m_paddle.draw(target);
		m_ball.draw(target);
	}
}
