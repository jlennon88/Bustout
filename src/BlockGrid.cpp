#include "BlockGrid.h"

#include <cassert>
#include <stdexcept>

namespace bustout
{
	BlockGrid::BlockGrid(int xCount, int yCount)
		: m_xCount(xCount)
		, m_yCount(yCount)
		, m_blocks(nullptr)
	{
		assert(xCount > 0);
		assert(yCount > 0);

		m_blocks = std::make_unique<int>(xCount * yCount);

		if (m_blocks.get() == nullptr)
			throw std::runtime_error("failed to allocate memory for BlockGrid");

		centreGrid();
	}

	void BlockGrid::setBlockHealth(int x, int y, int health) noexcept
	{
		assert(x >= 0 && x < m_xCount);
		assert(y >= 0 && y < m_yCount);

		const int idx = x + y * m_xCount;
		m_blocks.get()[idx] = health;
	}


	int BlockGrid::getBlockHealth(int x, int y) const noexcept
	{
		assert(x >= 0 && x < m_xCount);
		assert(y >= 0 && y < m_yCount);

		const int idx = x + y * m_xCount;
		return m_blocks.get()[idx];
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

	void BlockGrid::setGridCentre(const sf::Vector2f& position) noexcept
	{
		m_position = sf::Vector2f{ -0.5f * getGridWidth(), -0.5f * getGridWidth() } + position;
	}

	sf::Vector2f BlockGrid::getGridCentre() const noexcept
	{
		return m_position + sf::Vector2f{ 0.5f * getGridWidth(), 0.5f * getGridWidth() };
	}

	void BlockGrid::centreGrid() noexcept
	{
		m_position = { -0.5f * getGridWidth(), -0.5f * getGridWidth() };
	}
}