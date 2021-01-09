#include "AnimatedSprite.h"

#include "maths.h"

#include <cassert>

namespace bustout
{
	AnimatedSprite::AnimatedSprite(const std::string& filename)
		: Sprite(filename)
	{
	}

	void AnimatedSprite::setFrameCount(int frameCount)
	{
		assert(frameCount > 0);
		m_frameCount = frameCount;
	}

	void AnimatedSprite::setFrameRect(const sf::IntRect& rect)
	{
		assert(rect.width > 0);
		assert(rect.height > 0);
		m_frameRect = rect;
		setTextureRect(rect);
	}

	void AnimatedSprite::setFrameDelta(const sf::Vector2i& delta)
	{
		assert(delta.x > 0 || delta.y > 0);
		m_frameDelta = delta;
	}

	void AnimatedSprite::setFrameRate(float frameRate)
	{
		assert(frameRate > 0.0f);
		m_frameRate = frameRate;
	}

	void AnimatedSprite::update(float elapsedTime)
	{
		m_time += elapsedTime;
		const int frameNumber = static_cast<int>(m_time * m_frameRate) % m_frameCount;
		if (frameNumber != m_frameNumber)
		{
			m_frameNumber = frameNumber;
			m_sprite.setTextureRect(
				{
					m_frameRect.left + frameNumber * m_frameDelta.x,
					m_frameRect.top + frameNumber * m_frameDelta.y,
					m_frameRect.width,
					m_frameRect.height,
				}
			);
		}
	}
}
