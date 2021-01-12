#pragma once

#include <memory>
#include <stack>

#include <SFML/Graphics.hpp>

namespace bustout
{
	class UIElement
	{
	public:

		virtual ~UIElement() = default;

		virtual void onClick() noexcept {}
		virtual void onRelease() noexcept {}

		const sf::Vector2f& getExtent() const noexcept { return m_extent; }
		void setPosition(const sf::Vector2f& position) noexcept { m_position = position; }
		const sf::Vector2f& getLocalPosition() const noexcept { return m_position; }
		sf::Vector2f getGlobalPosition() const noexcept
		{
			if (m_parent)
				return m_position + m_parent->getGlobalPosition();
			else
				return m_position;
		}

		virtual void draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition = {}) = 0;

		void setParent(UIElement* parent) noexcept { m_parent = parent; }
		UIElement* getParent() noexcept { return m_parent; }
		const UIElement* getParent() const noexcept { return m_parent; }

	protected:
		sf::Vector2f m_extent{};
		sf::Vector2f m_position{};

	private:
		UIElement* m_parent = nullptr;

	};

	using UIElementRef = std::shared_ptr<UIElement>;
}