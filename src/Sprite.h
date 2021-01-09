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

		void draw(sf::RenderWindow& window, const sf::Vector2f& position) noexcept;
	protected:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
	};
}