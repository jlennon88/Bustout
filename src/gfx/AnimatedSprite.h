#pragma once

#include "Sprite.h"

namespace bustout
{
	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(const std::string& filename);

		void setFrameCount(int frameCount);
		void setFrameRect(const sf::IntRect& rect);
		void setFrameDelta(const sf::Vector2i& delta);
		void setFrameRate(float frameRate);
		void update(float elapsedTime);
	private:
		float m_time = 0.0f;
		float m_frameRate = 24.0f;
		int m_frameCount = 1;
		int m_frameNumber = 0;
		sf::IntRect m_frameRect{};
		sf::Vector2i m_frameDelta{};
	};
}