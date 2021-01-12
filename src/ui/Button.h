#pragma once

#include "UIElement.h"
#include "Text.h"

#include "gfx/Sprite.h"
#include <functional>
#include <string>

namespace bustout
{
	class Button final : public UIElement
	{
	public:
		using EventCallback = std::function<void(void)>;

		Button(
			  EventCallback onClickCallback
			, EventCallback onReleaseCallback
			, const std::string& text
		);

		void setText(const std::string& text);
		void setPadding(float padding) noexcept { m_padding = padding; }

		virtual void onClick() noexcept override final;
		virtual void onRelease() noexcept override final;

		void setOnClickCallback(EventCallback callback) noexcept { m_onClickCallback = callback; }
		void setOnReleaseCallback(EventCallback callback) noexcept { m_onReleaseCallback = callback; }

		virtual void draw(sf::RenderTarget& target, const sf::Vector2f& parentPosition = {}) override final;
	private:
		EventCallback m_onClickCallback;
		EventCallback m_onReleaseCallback;

		bool m_buttonState = false;
		Text m_text;
		Sprite m_sprite;
		float m_padding = 2.0f;
	};
}