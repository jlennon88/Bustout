#pragma once

#include "game/Shapes.h"

#include <SFML/Graphics.hpp>

#include <tuple>
#include <vector>

namespace bustout
{
	class DebugRenderer
	{
	public:
		using ObjectCollectionSet = std::tuple<
			  std::vector<const Circle*>
			, std::vector<const Capsule*>
			, std::vector<const Rectangle*>
		>;

		template<typename T>
		void registerObject(const T& object);

		template<typename T>
		void removeObject(const T& object);

		void draw(sf::RenderWindow& window) const;

		void setOutlineColour(sf::Color colour) noexcept;
		void setFillColour(sf::Color colour) noexcept;

		static DebugRenderer& get() noexcept;
	private:
		DebugRenderer() = default;

		sf::Color m_outlineColour{};// { 0x33, 0x33, 0x33, 0xFF };
		sf::Color m_fillColor = { 0, 0, 0, 0 };

		ObjectCollectionSet m_objects{};
	};

	void drawLine(sf::RenderTarget& target, const Line& line, const sf::Color& colour = sf::Color::Blue);
	void debugCircleRectCollision(sf::RenderTarget& target, const Circle& circle, const Rectangle& rect);
}