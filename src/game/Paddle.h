#pragma once

#include <SFML/System.hpp>

#include "Shapes.h"
#include "gfx/Sprite.h"
#include "gfx/AnimatedSprite.h"

namespace bustout
{
	class Paddle
	{
	public:
		Paddle(const sf::Vector2f& initialPosition = {});
		Paddle(const Paddle&) = delete;
		Paddle(Paddle&&) = delete;
		~Paddle();

		void setPosition(const sf::Vector2f& position) noexcept { m_shape.position = position; }
		const sf::Vector2f& getPosition() const noexcept { return m_shape.position; }
		const sf::Vector2f& getPrevPosition() const noexcept { return m_prevPosition; }

		void setSpeed(float speed) noexcept { m_speed = speed; }
		float getSpeed() const noexcept { return m_speed; }

		const Capsule& getShape() const noexcept { return m_shape; }

		void update(float elapsedTime) noexcept;

		void draw(sf::RenderTarget& target);
	private:
		AnimatedSprite m_beamSprite;
		Sprite m_endSprite;

		Capsule m_shape;
		float m_speed = 0.7f;
		sf::Vector2f m_prevPosition;
	};
}