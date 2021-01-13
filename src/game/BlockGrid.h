#pragma once

#include <SFML/System.hpp>

#include "gfx/Sprite.h"
#include "Shapes.h"
#include "Ball.h"

#include <vector>

namespace bustout
{
	class BlockGrid
	{
	public:
		BlockGrid(int xCount, int yCount);
		~BlockGrid();

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

		sf::Vector2f getGridCentre() const noexcept;

		const Rectangle& getAABB() const noexcept { return m_aabb; }

		// returns true if a block lost health
		bool handleCollision(Ball& ball) noexcept;

		void draw(sf::RenderTarget& target);
		
		Rectangle getBlock(int x, int y) const noexcept;

		int getRemainingBlocks() const noexcept { return m_remainingBlocks; }
	private:
		std::pair<int, int> getPointCoords(const sf::Vector2f& point) const noexcept;

		int m_xCount;
		int m_yCount;

		int m_remainingBlocks;

		float m_blockWidth = 0.15f;
		float m_blockHeight = 0.05f;

		sf::Vector2f m_position{ 0.0f, 0.0f };

		Sprite m_blockSprite;

		Rectangle m_aabb;

		std::vector<int> m_blocks;
#ifdef BUSTOUT_DEBUG
		std::vector<Rectangle> m_debugBlocks;
#endif
	};
}