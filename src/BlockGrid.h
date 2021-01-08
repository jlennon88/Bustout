#pragma once

#include <SFML/System.hpp>

#include "Block.h"

#include <memory>

namespace bustout
{
	class BlockGrid
	{
	public:
		BlockGrid(int xCount, int yCount);

		void setBlockHealth(int x, int y, int health) noexcept;
		int getBlockHealth(int x, int y) const noexcept;

		int getXCount() const noexcept { return m_xCount; }
		int getYCount() const noexcept { return m_yCount; }

		void setBlockWidth(float blockWidth) noexcept;
		void setBlockHeight(float blockHeight) noexcept;

		float getBlockWidth() const noexcept { return m_blockWidth; }
		float getBlockHeight() const noexcept { return m_blockHeight; }

		void setGridWidth(float gridWidth) noexcept;
		void setGridHeight(float gridHeight) noexcept;

		float getGridWidth() const noexcept { return getBlockWidth() * m_xCount; }
		float getGridHeight() const noexcept { return getBlockHeight() * m_yCount; }

		// sets the top-left position of the grid
		void setGridPosition(const sf::Vector2f& position) noexcept { m_position = position; }
		// returns the top-left position of the grid
		const sf::Vector2f& getGridPosition() const noexcept { return m_position; }

		void setGridCentre(const sf::Vector2f& position) noexcept;
		sf::Vector2f getGridCentre() const noexcept;

		// sets the position of the grid so that its centre is at ( 0.0f, 0.0f )
		void centreGrid() noexcept;
	private:
		int m_xCount;
		int m_yCount;

		float m_blockWidth = 100.0f;
		float m_blockHeight = 50.0f;

		sf::Vector2f m_position{ 0.0f, 0.0f };

		std::unique_ptr<int> m_blocks;
	};
}