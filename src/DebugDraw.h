#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "BlockGrid.h"
#include "PowerUp.h"

#include <SFML/Graphics.hpp>

#include <tuple>
#include <vector>

namespace bustout
{
	class DebugRenderer
	{
	public:
		using ObjectCollectionSet = std::tuple<
			  std::vector<const Ball*>
			, std::vector<const Paddle*>
			, std::vector<const BlockGrid*>
			, std::vector<const PowerUp*>
		>;

		template<typename T>
		void registerObject(const T& object) noexcept;

		template<typename T>
		void removeObject(const T& object) noexcept;

		void draw(sf::RenderWindow& window) const;

		void setOutlineColour(sf::Color colour) noexcept;
		void setFillColour(sf::Color colour) noexcept;

		static DebugRenderer& get() noexcept;
	private:
		DebugRenderer() = default;

		sf::Color m_outlineColour{ 0x33, 0x33, 0x33, 0xFF };
		sf::Color m_fillColor = { 0, 0, 0, 0 };

		ObjectCollectionSet m_objects{};
	};
}