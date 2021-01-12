#include "Paddle.h"

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

#include "maths.h"

namespace bustout
{
	const static sf::Vector2f s_endSpriteScale = { 0.15f / 128.0f, 0.15f / 128.0f };

	Paddle::Paddle(const sf::Vector2f& initialPosition)
		: m_beamSprite("paddle_beam.png")
		, m_endSprite("paddle_end.png")
		, m_shape({ initialPosition, 0.075f, 0.02f })
	{
#ifdef BUSTOUT_DEBUG
		DebugRenderer::get().registerObject(m_shape);
#endif

		m_beamSprite.setFrameRect({ 0, 0, 128, 24 });
		m_beamSprite.setFrameDelta({ 0, 24 });
		m_beamSprite.setFrameCount(6);
		m_beamSprite.setFrameRate(12.0f);
		m_beamSprite.setScale({ 0.15f / 128.0f, 0.15f / 128.0f });
		
		auto& endSprite = m_endSprite.getSprite();
		endSprite.setScale(s_endSpriteScale);
		endSprite.setOrigin(1.0f * endSprite.getTextureRect().width, endSprite.getTextureRect().height * 0.5f);
	}

	Paddle::~Paddle()
	{
#ifdef BUSTOUT_DEBUG
		DebugRenderer::get().removeObject(m_shape);
#endif
	}

	void Paddle::update(float elapsedTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			m_shape.position.x -= m_speed * elapsedTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			m_shape.position.x += m_speed * elapsedTime;

		const float halfSpan = m_shape.radius + m_shape.halfLength;
		m_shape.position.x = clamp(m_shape.position.x, halfSpan - 1, 1 - halfSpan);

		m_beamSprite.update(elapsedTime);
	}

	void Paddle::draw(sf::RenderTarget& target)
	{
		m_endSprite.setScale(-s_endSpriteScale);
		m_endSprite.draw(target, getPosition() + sf::Vector2f(m_shape.halfLength, 0.0f));
		m_endSprite.setScale(s_endSpriteScale);
		m_endSprite.draw(target, getPosition() - sf::Vector2f(m_shape.halfLength, 0.0f));

		m_beamSprite.draw(target, getPosition());
	}
}