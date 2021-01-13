#include "Sprite.h"

#include <filesystem>
#include <stdexcept>

namespace bustout
{
	using path = std::filesystem::path;
	const static path s_TextureAssetPath = ASSET_DIR "/textures";

	Sprite::Sprite(const std::string& textureFilename)
	{
		const path texturePath = s_TextureAssetPath / textureFilename;
		if (!m_texture.loadFromFile(texturePath.string()))
			throw std::runtime_error("failed to load texture");

		m_sprite.setTexture(m_texture);
		m_sprite.setScale(1 / (float)m_sprite.getTextureRect().width, 1 / (float)m_sprite.getTextureRect().height);
		m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
	}

	void Sprite::setTextureRect(const sf::IntRect& rect)
	{
		m_sprite.setTextureRect(rect);
		m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
		m_sprite.setScale(1 / (float)m_sprite.getTextureRect().width, 1 / (float)m_sprite.getTextureRect().height);
	}

	void Sprite::setScale(const sf::Vector2f& scale)
	{
		m_sprite.setScale(scale.x, scale.y);
	}

	void Sprite::setColour(const sf::Color& colour)
	{
		m_sprite.setColor(colour);
	}

	void Sprite::draw(sf::RenderTarget& target, const sf::Vector2f& position) noexcept
	{
		m_sprite.setPosition(position);
		target.draw(m_sprite);
	}
}
