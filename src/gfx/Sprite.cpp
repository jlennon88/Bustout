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
	}

	void Sprite::setTextureRect(const sf::IntRect& rect)
	{
		m_sprite.setTextureRect(rect);
		m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
	}

	void Sprite::setScale(const sf::Vector2f& scale)
	{
		m_sprite.setScale(scale);
	}

	void Sprite::draw(sf::RenderTarget& target, const sf::Vector2f& position) noexcept
	{
		m_sprite.setPosition(position);
		target.draw(m_sprite);
	}
}
