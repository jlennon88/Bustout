#pragma once

#include <SFML/System.hpp>

#include "Shapes.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

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

		void setSpeed(float speed) noexcept { m_speed = speed; }
		float getSpeed() const noexcept { return m_speed; }

		const Capsule& getShape() const noexcept { return m_shape; }

		void update(float elapsedTime);

		void draw(sf::RenderWindow& window);
	private:
		AnimatedSprite m_beamSprite;
		Sprite m_endSprite;

		Capsule m_shape;
		float m_speed = 0.5f;
	};
}