#include "DebugDraw.h"

#include "maths.h"

namespace bustout
{
	template<typename T>
	inline static std::vector<const T*>& selectVector(DebugRenderer::ObjectCollectionSet& objectCollectionSet) noexcept
	{
		return std::get<std::vector<const T*>>(objectCollectionSet);
	}

	template<typename T>
	void DebugRenderer::registerObject(const T& object)
	{
		auto& objectVector = selectVector<T>(m_objects);
		if (std::find(std::begin(objectVector), std::end(objectVector), &object) == std::end(objectVector))
			objectVector.push_back(&object);
	}

	template<typename T>
	void DebugRenderer::removeObject(const T& object)
	{
		auto& objectVector = selectVector<T>(m_objects);
		auto pos = std::find(std::begin(objectVector), std::end(objectVector), &object);
		if (pos != std::end(objectVector))
			objectVector.erase(pos);
	}

	inline static void renderObjects(
		  sf::RenderWindow& window
		, const std::vector<const Circle*>& circles
		, const sf::Color& fillColour
		, const sf::Color& outlineColour
	)
	{
		sf::CircleShape circle;
		circle.setOutlineThickness(-0.005f);
		circle.setFillColor(fillColour);
		circle.setOutlineColor(outlineColour);

		for (const auto c : circles)
		{
			circle.setPosition(c->position);
			circle.setOrigin({ c->radius, c->radius });
			circle.setRadius(c->radius);
			window.draw(circle);
		}
	}

	inline static void renderObjects(
		  sf::RenderWindow& window
		, const std::vector<const Capsule*>& capsules
		, const sf::Color& fillColour
		, const sf::Color& outlineColour
	)
	{
		sf::CircleShape circle;
		circle.setOutlineThickness(-0.005f);
		circle.setFillColor(fillColour);
		circle.setOutlineColor(outlineColour);

		sf::RectangleShape rectangle;
		rectangle.setOutlineThickness(-0.005f);
		rectangle.setFillColor(fillColour);
		rectangle.setOutlineColor(outlineColour);

		for (const auto capsule : capsules)
		{
			// draw end points
			circle.setOrigin({ capsule->radius, capsule->radius });
			circle.setRadius(capsule->radius);
			circle.setPosition(capsule->position - sf::Vector2f(-capsule->halfLength, 0.0f));
			window.draw(circle);
			circle.setPosition(capsule->position + sf::Vector2f(-capsule->halfLength, 0.0f));
			window.draw(circle);
			
			// draw body
			rectangle.setPosition(capsule->position);

			rectangle.setSize({ 2 * capsule->halfLength, 2 * capsule->radius });
			rectangle.setOrigin({ capsule->halfLength, capsule->radius });
			window.draw(rectangle);
		}
	}

	inline static void renderObjects(
		  sf::RenderWindow& window
		, const std::vector<const Rectangle*>& rects
		, const sf::Color& fillColour
		, const sf::Color& outlineColour
	)
	{
	}

	template<int IDX>
	inline static void drawObjectCollection(
		  sf::RenderWindow& window
		, const DebugRenderer::ObjectCollectionSet& objectCollectionSet
		, const sf::Color& fillColour
		, const sf::Color& outlineColour
	)
	{
		const auto& objectCollection = std::get<IDX>(objectCollectionSet);
		
		renderObjects(window, objectCollection, fillColour, outlineColour);

		return drawObjectCollection<IDX - 1>(window, objectCollectionSet, fillColour, outlineColour);
	}

	template<>
	inline static void drawObjectCollection<-1>(
		  sf::RenderWindow&
		, const DebugRenderer::ObjectCollectionSet&
		, const sf::Color&
		, const sf::Color&
	)
	{
		return;
	}

	void DebugRenderer::draw(sf::RenderWindow& window) const
	{
		constexpr int IDX0 = (int)std::tuple_size<ObjectCollectionSet>()() - 1;
		drawObjectCollection<IDX0>(window, m_objects, m_fillColor, m_outlineColour);
	}

	void DebugRenderer::setOutlineColour(sf::Color colour) noexcept
	{
		m_outlineColour = colour;
	}

	void DebugRenderer::setFillColour(sf::Color colour) noexcept
	{
		m_fillColor = colour;
	}

	DebugRenderer& DebugRenderer::get() noexcept
	{
		static DebugRenderer inst;
		return inst;
	}

	template void DebugRenderer::registerObject(const Circle& object);
	template void DebugRenderer::registerObject(const Capsule& object);
	template void DebugRenderer::registerObject(const Rectangle& object);

	template void DebugRenderer::removeObject(const Circle& object);
	template void DebugRenderer::removeObject(const Capsule& object);
	template void DebugRenderer::removeObject(const Rectangle& object);
}