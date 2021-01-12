#include "Canvas.h"

namespace bustout
{
	constexpr bool pointInRect(const sf::Vector2f& point, const sf::FloatRect& rect) noexcept
	{
		const bool isLeft = point.x < rect.left;
		const bool isRight = point.x > rect.left + rect.width;
		const bool isAbove = point.y > rect.top;
		const bool isBelow = point.y < rect.top - rect.height;

		return !(isLeft || isRight || isAbove || isBelow);
	}

	Canvas::Canvas(int screenWidth, int screenHeight)
	{
		m_extent = { (float)screenWidth, (float)screenHeight };
	}

	void Canvas::onClick() noexcept
	{
		const sf::Vector2i mousePos = sf::Mouse::getPosition();
		const sf::Vector2f relativePos = sf::Vector2f{ (float)mousePos.x, (float)mousePos.y } - getGlobalPosition();
		for (auto& elem : m_elements)
		{
			const auto rect = sf::FloatRect{
				elem->getLocalPosition().x,
				elem->getLocalPosition().y,
				elem->getExtent().x,
				elem->getExtent().y,
			};

			if (pointInRect(relativePos, rect))
				elem->onClick();
		}
	}

	void Canvas::onRelease() noexcept
	{
		for (auto& elem : m_elements)
			elem->onRelease();
	}

	void Canvas::update(sf::Window& window)
	{
	}

	void Canvas::draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition)
	{
		const sf::Vector2f globalPosition = m_position + parentPosition;
		for (auto& elem : m_elements)
			elem->draw(target, parentPosition);
	}
}
