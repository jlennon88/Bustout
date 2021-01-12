#include "Text.h"

namespace bustout
{
	Text::Text(const std::string& text)
	{
		constexpr const char* FontFile = ASSET_DIR "/fonts/arial.ttf";
		m_font.loadFromFile(FontFile);
		m_text.setFont(m_font);
		setText(text);
	}

	void Text::draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition)
	{
		m_text.setPosition(m_position + parentPosition);
		target.draw(m_text);
	}

	void Text::setText(const std::string& text)
	{
		m_text.setString(text);
		m_extent.x = m_text.getLocalBounds().width;
		m_extent.y = m_text.getLocalBounds().height;
		m_text.setOrigin(0.5f * m_extent);
	}
}