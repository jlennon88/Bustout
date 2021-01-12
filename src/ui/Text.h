#pragma once

#include "UIElement.h"

namespace bustout
{
	class Text final : public UIElement
	{
	public:
		Text(const std::string& text = "Text");

		virtual void draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition = {}) override final;

		void setText(const std::string& text);
	private:
		sf::Text m_text;
		sf::Font m_font;
	};
}