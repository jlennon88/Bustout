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
	{
#ifdef BUSTOUT_DEBUG
		DebugRenderer::get().registerObject(m_shape);
#endif
	}

	Ball::~Ball()
	{
#ifdef BUSTOUT_DEBUG
		DebugRenderer::get().removeObject(m_shape);
#endif
	}

	void Ball::setPosition(const sf::Vector2f& position) noexcept
	{
		m_shape.position = position;
	}

	void Ball::setVelocity(const sf::Vector2f& velocity) noexcept
	{
		m_velocity = velocity;
	}

	void Ball::update(float elapsedTime)
	{
		m_shape.position += m_velocity * elapsedTime;
	}

	void Ball::draw(sf::RenderTarget& target)
	{
		m_sprite.draw(target, m_shape.position);
	}
}