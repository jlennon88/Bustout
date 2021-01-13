#include "BlockGrid.h"

#include "maths.h"
#include "collision.h"

#include <array>
#include <cassert>
#include <stdexcept>

#ifdef BUSTOUT_DEBUG
#include "debug/DebugDraw.h"
#endif

#include <iostream>

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

		// generate pseudo-random block layout
		// - this can lead to unwinnable games since there
		//	 aren't checks on destructable blocks being
		//	 surrounded by indestructable blocks
		std::generate(std::begin(m_blocks), std::end(m_blocks), []() 
			{
				return rand() % 5 - 1;
			}
		);

		// count the number of blocks that have positive hp
		m_remainingBlocks = (int)std::count_if(std::begin(m_blocks), std::end(m_blocks), [](int hp)
			{
				return hp > 0;
			}
		);

		m_blockSprite.setScale(
			{
				m_blockWidth / m_blockSprite.getSprite().getTextureRect().width,
				m_blockHeight / m_blockSprite.getSprite().getTextureRect().height,
			}
		);

		m_aabb.topLeft = { -m_blockWidth * (m_xCount / 2.0f), m_blockHeight * (m_yCount / 2.0f) };
		m_aabb.widthHeight = { m_blockWidth * (m_xCount), m_blockHeight * (m_yCount) };
#ifdef BUSTOUT_DEBUG
		m_debugBlocks.resize(m_blocks.size());

		size_t idx = 0;
		const sf::Vector2f initPos = { -m_blockWidth * (m_xCount / 2.0f), m_blockHeight * (m_yCount / 2.0f) };
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
			blockPos.y -= m_blockHeight;
		}

		DebugRenderer::get().registerObject(m_aabb);
#endif
	}

	BlockGrid::~BlockGrid()
	{

#ifdef BUSTOUT_DEBUG
		size_t idx = 0;
		for (int y = 0; y < m_yCount; ++y)
			for (int x = 0; x < m_xCount; ++x)
				DebugRenderer::get().removeObject(m_debugBlocks[idx++]);
		DebugRenderer::get().removeObject(m_aabb);
#endif
	}

	void BlockGrid::setBlockHealth(int x, int y, int health) noexcept
	{
		assert(x >= 0 && x < m_xCount);
		assert(y >= 0 && y < m_yCount);

		const int idx = x + y * m_xCount;

		if (health > 0 && m_blocks[idx] <= 0)
			++m_remainingBlocks;
		else if (health <= 0 && m_blocks[idx] > 0)
			--m_remainingBlocks;

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

	bool BlockGrid::handleCollision(Ball& ball) noexcept
	{
		const auto ballAABB = ball.getAABB();

		if (testCollision_RectRect(ballAABB, m_aabb))
		{
			int xCount = 2;
			int yCount = 2;
			auto [x0, y0] = getPointCoords(ballAABB.topLeft);

			if (x0 < 0 || x0 + 1 >= m_xCount)
			{
				x0 = clamp(x0, 0, m_xCount - 1);
				xCount /= 2;
			}
			if (y0 < 0 || y0 + 1 >= m_yCount)
			{
				y0 = clamp(y0, 0, m_yCount - 1);
				yCount /= 2;
			}
			
			int idx = x0 + y0 * m_xCount;
			sf::Vector2f collisionNormal{};
			int colIdx = idx;
			bool didCollide = false;
			for (int y = y0; y < y0 + yCount; ++y)
			{
				for (int x = x0; x < x0 + xCount; ++x)
				{
					// ignore empty spaces defined by 0
					if (m_blocks[idx] != 0)
					{
						Rectangle block = getBlock(x, y);
						const auto collisionData = testCollision_CircleRect(ball.getShape(), block);
						if (collisionData.has_value())
						{
							const auto blockMid = block.topLeft + sf::Vector2f{ 0.5f * block.widthHeight.x, -0.5f * block.widthHeight.y };
							const bustout::Line mouseToBlock = { ball.getPosition(), blockMid };
							for (const auto edge : getEdges(block))
							{
								if (testCollision_LineLine(mouseToBlock, edge))
								{
									const auto normal = bustout::normalise(bustout::cross(1.0f, edge.p1 - edge.p0));
									const auto edgeMidPoint = 0.5f * (edge.p0 + edge.p1);
									const auto ballToEdgeDist = bustout::abs(bustout::dot(normal, ball.getPosition() - edgeMidPoint));
									const auto blockToEdgeDist = bustout::abs(bustout::dot(normal, edgeMidPoint - blockMid));
									const auto radSum = ball.getShape().radius + 0.5f * bustout::abs(bustout::dot(normal, block.widthHeight));
									const auto delta = bustout::clamp_ge_zero(radSum - (blockToEdgeDist + ballToEdgeDist));
									ball.setPosition(ball.getPosition() + delta * normal);
									didCollide = true;
									collisionNormal = normal;
									colIdx = idx;
								}
							}
						}
					}
					++idx;
				}
				idx += m_xCount - xCount;
			}

			if (didCollide)
			{
				ball.setVelocity(reflect(ball.getVelocity(), collisionNormal));
				if (m_blocks[colIdx] > 0)
				{
					if (--m_blocks[colIdx] == 0)
						--m_remainingBlocks;
					return true;
				}
			}
		}
		return false;
	}

	void BlockGrid::draw(sf::RenderTarget& target)
	{
		size_t idx = 0;

		const sf::Vector2f initPos = { -m_blockWidth * (-0.5f + m_xCount / 2.0f), m_blockHeight * (-0.5f + m_yCount / 2.0f) };
		sf::Vector2f blockPosition = initPos;
		for (int y = 0; y < m_yCount; ++y)
		{
			blockPosition.x = initPos.x;
			for (int x = 0; x < m_xCount; ++x)
			{
				int blockHealth = m_blocks[idx++];
				sf::Color blockColour = { 0xCC, 0xCC, 0xCC, 0xFF };
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
			blockPosition.y -= m_blockHeight;
		}
	}

	Rectangle BlockGrid::getBlock(int x, int y) const noexcept
	{
		assert(x >= 0);
		assert(y >= 0);
		assert(x < m_xCount);
		assert(y < m_yCount);

		Rectangle rect;
		rect.topLeft = { m_aabb.topLeft.x + x * m_blockWidth, m_aabb.topLeft.y - y * m_blockHeight };
		rect.widthHeight = { m_blockWidth, m_blockHeight };
		return rect;
	}

	std::pair<int, int> BlockGrid::getPointCoords(const sf::Vector2f& point) const noexcept
	{
		int x = static_cast<int>((point.x - m_aabb.topLeft.x) / m_blockWidth);
		int y = static_cast<int>((m_aabb.topLeft.y - point.y) / m_blockHeight);
		return { x, y };
	}
}