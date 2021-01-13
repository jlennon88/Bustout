#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace bustout
{
	class Sprite
	{
	public:
		Sprite(const std::string& textureFilename);

		void setTextureRect(const sf::IntRect& rect);
		void setScale(const sf::Vector2f& scale);
		void setColour(const sf::Color& colour);

		void draw(sf::RenderTarget& target, const sf::Vector2f& position) noexcept;

		sf::Sprite& getSprite() noexcept { return m_sprite; }
		const sf::Sprite& getSprite() const noexcept { return m_sprite; }
	protected:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
	};
}