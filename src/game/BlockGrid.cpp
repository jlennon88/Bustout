#include "BlockGrid.h"

#include "maths.h"

#include <cassert>
#include <stdexcept>

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

namespace bustout
{
	BlockGrid::BlockGrid(int xCount, int yCount)
		: m_xCount(xCount)
		, m_yCount(yCount)
		, m_blockSprite("block.png")
	{
		assert(xCount > 0);
		assert(yCount > 0);

		m_blocks.resize((size_t)xCount * (size_t)yCount);
		std::generate(std::begin(m_blocks), std::end(m_blocks), []() 
			{
				return rand() % 5 - 1;
			}
		);

		m_blockSprite.setScale(
			{
				m_blockWidth * 1 / m_blockSprite.getSprite().getTextureRect().width,
				m_blockHeight * 1 / m_blockSprite.getSprite().getTextureRect().height,
			}
		);

#ifdef BUSTOUT_DEBUG
		m_debugBlocks.resize(m_blocks.size());

		size_t idx = 0;
		const sf::Vector2f initPos = { -m_blockWidth * (m_xCount / 2.0f), -m_blockHeight * (m_yCount / 2.0f) };
		sf::Vector2f blockPos = initPos;
		for (int y = 0; y < m_yCount; ++y)
		{
			blockPos.x = initPos.x;
			for (int x = 0; x < m_xCount; ++x)
			{
				auto& debugBlock = m_debugBlocks[idx++];
				DebugRenderer::get().registerObject(debugBlock);

				debugBlock.topLeft = blockPos;
				debugBlock.widthHeight = { m_blockWidth, m_blockHeight };

				blockPos.x += m_blockWidth;
			}
			blockPos.y += m_blockHeight;
		}
#endif
	}

	BlockGrid::~BlockGrid()
	{

#ifdef BUSTOUT_DEBUG
		m_debugBlocks.resize(m_blocks.size());

		size_t idx = 0;
		for (int y = 0; y < m_yCount; ++y)
			for (int x = 0; x < m_xCount; ++x)
				DebugRenderer::get().removeObject(m_debugBlocks[idx++]);
#endif
	}

	void BlockGrid::setBlockHealth(int x, int y, int health) noexcept
	{
		assert(x >= 0 && x < m_xCount);
		assert(y >= 0 && y < m_yCount);

		const int idx = x + y * m_xCount;
		m_blocks[idx] = health;
	}


	int BlockGrid::getBlockHealth(int x, int y) const noexcept
	{
		assert(x >= 0 && x < m_xCount);
		assert(y >= 0 && y < m_yCount);

		const int idx = x + y * m_xCount;
		return m_blocks[idx];
	}

	void BlockGrid::setBlockWidth(float blockWidth) noexcept
	{
		assert(blockWidth > 0.0f);
		m_blockWidth = blockWidth;
	}

	void BlockGrid::setBlockHeight(float blockHeight) noexcept
	{
		assert(blockHeight > 0.0f);
		m_blockHeight = blockHeight;
	}

	void BlockGrid::setGridWidth(float gridWidth) noexcept
	{
		assert(gridWidth > 0.0f);
		setBlockWidth(gridWidth / static_cast<float>(m_xCount));
	}

	void BlockGrid::setGridHeight(float gridHeight) noexcept
	{
		assert(gridHeight > 0.0f);
		setBlockHeight(gridHeight / static_cast<float>(m_yCount));
	}

	sf::Vector2f BlockGrid::getGridCentre() const noexcept
	{
		return m_position + sf::Vector2f{ 0.5f * getGridWidth(), 0.5f * getGridWidth() };
	}

	void BlockGrid::handleCollision(Ball& ball) noexcept
	{
	}

	void BlockGrid::draw(sf::RenderTarget& target)
	{
		size_t idx = 0;

		const sf::Vector2f initPos = { -m_blockWidth * (-0.5f + m_xCount / 2.0f), -m_blockHeight * (-0.5f + m_yCount / 2.0f) };
		sf::Vector2f blockPosition = initPos;
		for (int y = 0; y < m_yCount; ++y)
		{
			blockPosition.x = initPos.x;
			for (int x = 0; x < m_xCount; ++x)
			{
				int blockHealth = m_blocks[idx++];
				sf::Color blockColour = sf::Color::White;
				if (blockHealth >= 0)
				{
					switch (blockHealth)
					{
					case 0:
						blockColour = sf::Color::Transparent;
						break;
					case 1:
						blockColour = sf::Color::Green;
						break;
					case 2:
						blockColour = sf::Color::Blue;
						break;
					case 3:
					default:
						blockColour = sf::Color::Red;
						break;
					}
				}
				m_blockSprite.setColour(blockColour);
				m_blockSprite.draw(target, blockPosition);
				blockPosition.x += m_blockWidth;
			}
			blockPosition.y += m_blockHeight;
		}
	}
}