#include "Ball.h"

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

namespace bustout
{
	Ball::Ball(float radius, const sf::Vector2f& initialPosition, const sf::Vector2f& initialVelocity)
		: m_sprite("ball.png")
		, m_shape({ initialPosition, radius })
		, m_velocity(initialVelocity)
		, m_prevPosition(initialPosition)
	{
		m_aabb.topLeft = m_shape.position - sf::Vector2f(m_shape.radius, -m_shape.radius);
		m_aabb.widthHeight = { 2.0f * radius, 2.0f * radius };
#ifdef BUSTOUT_DEBUG
		DebugRenderer::get().registerObject(m_shape);
		DebugRenderer::get().registerObject(m_aabb);
#endif
		
		m_sprite.setScale({ m_shape.radius * 2 / m_sprite.getSprite().getTextureRect().width, m_shape.radius  * 2/ m_sprite.getSprite().getTextureRect().height });
	}

	Ball::~Ball()
	{
#ifdef BUSTOUT_DEBUG
		DebugRenderer::get().removeObject(m_shape);
		DebugRenderer::get().removeObject(m_aabb);
#endif
	}

	void Ball::setPosition(const sf::Vector2f& position) noexcept
	{
		m_shape.position = position;
		m_aabb.topLeft = m_shape.position - sf::Vector2f(m_shape.radius, -m_shape.radius);
	}

	void Ball::setVelocity(const sf::Vector2f& velocity) noexcept
	{
		m_velocity = velocity;
	}

	void Ball::update(float elapsedTime) noexcept
	{
		m_prevPosition = m_shape.position;
		m_shape.position += m_velocity * elapsedTime;

		if (m_shape.position.x + m_shape.radius > 1)
		{
			m_shape.position.x = 1 - m_shape.radius;
			m_velocity.x = -m_velocity.x;
		}
		else if (m_shape.position.x - m_shape.radius < -1)
		{
			m_shape.position.x = m_shape.radius - 1;
			m_velocity.x = -m_velocity.x;
		}

		if (m_shape.position.y + m_shape.radius > 1)
		{
			m_shape.position.y = 1 - m_shape.radius;
			m_velocity.y = -m_velocity.y;
		}
		else if (m_shape.position.y - m_shape.radius < -1)
		{
			m_shape.position.y = m_shape.radius - 1;
			m_velocity.y = -m_velocity.y;
		}

		m_aabb.topLeft = m_shape.position - sf::Vector2f(m_shape.radius, -m_shape.radius);
	}

	void Ball::draw(sf::RenderTarget& target)
	{
		m_sprite.draw(target, m_shape.position);
	}
}