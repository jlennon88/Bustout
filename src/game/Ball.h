#pragma once

#include <SFML/System.hpp>

#include "Shapes.h"
#include "gfx/Sprite.h"

namespace bustout
{
	class Ball
	{
	public:
		Ball(
			  float radius = 10.0f
			, const sf::Vector2f& initialPosition = {}
			, const sf::Vector2f& initialVelocity = {}
		);
		Ball(const Ball&) = delete;
		Ball(Ball&&) = delete;
		~Ball();

		void setPosition(const sf::Vector2f& position) noexcept;
		void setVelocity(const sf::Vector2f& velocity) noexcept;

		const sf::Vector2f& getPosition() const noexcept { return m_shape.position; }
		const sf::Vector2f& getVelocity() const noexcept { return m_velocity; }
		const Circle& getShape() const noexcept { return m_shape; }

		void update(float elapsedTime);

		void draw(sf::RenderTarget& target);

	private:
		Sprite m_sprite;
		Circle m_shape;
		sf::Vector2f m_velocity;
	};
}
