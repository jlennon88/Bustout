#include "Bustout.h"

#include "maths.h"
#include "collision.h"

namespace bustout
{
	Bustout::Bustout()
		: m_paddle({ 0.0f, -0.8f })
	{
	}

	void Bustout::update(float elapsedTime) noexcept
	{
		m_paddle.update(elapsedTime);
		if (!m_ballFixed)
		{
			m_ball.update(elapsedTime);
			auto collisionData = testCollision_CircleCapsule(m_ball.getShape(), m_paddle.getShape());
			if (collisionData.has_value())
			{
				const auto disp = m_ball.getPosition() - collisionData.value();
				const float dist = m_paddle.getShape().radius + m_ball.getShape().radius - length(disp);
				const auto norm = normalise(disp);
				m_ball.setPosition(m_ball.getPosition() + norm * dist);

				const sf::Vector2f paddleVelocity = (m_paddle.getPosition() - m_paddle.getPrevPosition()) / elapsedTime;
				m_ball.setVelocity(normalise(reflect(m_ball.getVelocity(), norm) + paddleVelocity) * m_ballSpeed);
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				const sf::Vector2f paddleVelocity = (m_paddle.getPosition() - m_paddle.getPrevPosition()) / elapsedTime;
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
	void Bustout::draw(sf::RenderTarget& target)
	{
		m_paddle.draw(target);
		m_ball.draw(target);
	}
}
