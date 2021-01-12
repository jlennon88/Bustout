#include "Button.h"

#include "maths.h"

namespace bustout
{
	Button::Button(
		  EventCallback onClickCallback
		, EventCallback onReleaseCallback
		, const std::string& text
	)
		: m_onClickCallback(onClickCallback)
		, m_onReleaseCallback(onReleaseCallback)
		, m_sprite("button.png")
	{
		m_text.setParent(this);
		setText(text);
	}

	void Button::setText(const std::string& text)
	{
		m_text.setText(text);
		m_extent = m_text.getExtent() + sf::Vector2(2 * m_padding, 2 * m_padding);
		m_sprite.setScale(m_extent);
	}

	void Button::onClick() noexcept
	{
		if (!m_buttonState && m_onClickCallback)
		{
			m_onClickCallback();
			m_buttonState = true;
		}
	}
	void Button::onRelease() noexcept
	{
		if (m_buttonState && m_onReleaseCallback)
		{
			m_onReleaseCallback();
			m_buttonState = false;
		}
	}

	void Button::draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition)
	{
		const sf::Vector2f globalPosition = m_position + parentPosition;
		m_sprite.draw(target, globalPosition);

		m_text.draw(target, globalPosition);
	}
}