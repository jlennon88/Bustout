#pragma once

#include "UIElement.h"

#include <vector>

namespace bustout
{
	class Canvas final : public UIElement
	{
	public:
		Canvas(int screenWidth, int screenHeight);

		template<typename ElementType, typename ...Args>
		std::shared_ptr<ElementType> addElement(Args&&... args)
		{
			m_elements.emplace_back(std::make_shared<ElementType>(std::forward<Args>(args)...));
			return std::dynamic_pointer_cast<ElementType>(m_elements.back());
		}

		void update(sf::Window& window);

		virtual void draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition = {});
	private:
		std::vector<UIElementRef> m_elements;
	};
}