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
			  float radius = 0.02f
			, const sf::Vector2f& initialPosition = {}
			, const sf::Vector2f& initialVelocity = {}
		);
		Ball(const Ball&) = delete;
		Ball(Ball&&) = delete;
		~Ball();

		void setPosition(const sf::Vector2f& position) noexcept;
		void setVelocity(const sf::Vector2f& velocity) noexcept;

		const sf::Vector2f& getPosition() const noexcept { return m_shape.position; }
		const sf::Vector2f& getPrevPosition() const noexcept { return m_prevPosition; }
		const sf::Vector2f& getVelocity() const noexcept { return m_velocity; }
		const Circle& getShape() const noexcept { return m_shape; }

		void update(float elapsedTime) noexcept;

		void draw(sf::RenderTarget& target);

		const Rectangle& getAABB() const noexcept { return m_aabb; }

	private:
		Sprite m_sprite;
		Circle m_shape;
		Rectangle m_aabb;
		sf::Vector2f m_velocity;
		sf::Vector2f m_prevPosition;
	};
}
