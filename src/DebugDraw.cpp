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
	void DebugRenderer::registerObject(const T& object) noexcept
	{
		auto& objectVector = selectVector<T>();
		if (std::find(std::begin(objectVector), std::end(objectVector), &object) == std::end(objectVector))
			objectVector.push_back(&object);
	}

	template<typename T>
	void DebugRenderer::removeObject(const T& object) noexcept
	{
		auto& objectVector = selectVector<T>();
		auto pos = std::find(std::begin(objectVector), std::end(objectVector), &object);
		if (pos != std::end(objectVector))
			objectVector.erase(pos);
	}

	inline static void renderObjects(
		  sf::RenderWindow& window
		, const std::vector<const Ball*>& balls
		, const sf::Color& fillColour
		, const sf::Color& outlineColour
	)
	{
		sf::CircleShape circle;
		circle.setOutlineThickness(-2.0f);
		circle.setFillColor(fillColour);
		circle.setOutlineColor(outlineColour);
		for (const auto ball : balls)
		{
			circle.setPosition(ball->position);
			circle.setOrigin({ ball->radius, ball->radius });
			window.draw(circle);
		}
	}

	inline static void renderObjects(
		  sf::RenderWindow& window
		, const std::vector<const Paddle*>& paddles
		, const sf::Color& fillColour
		, const sf::Color& outlineColour
	)
	{
		sf::CircleShape circle;
		circle.setOutlineThickness(-2.0f);
		circle.setFillColor(fillColour);
		circle.setOutlineColor(outlineColour);

		sf::RectangleShape rectangle;
		rectangle.setOutlineThickness(-2.0f);
		rectangle.setFillColor(fillColour);
		rectangle.setOutlineColor(outlineColour);

		for (const auto paddle : paddles)
		{
			// draw end points
			circle.setOrigin({ paddle->radius, paddle->radius });
			circle.setPosition(paddle->pointA);
			window.draw(circle);
			circle.setPosition(paddle->pointB);
			window.draw(circle);
			
			// draw body
			rectangle.setPosition(0.5f * (paddle->pointA + paddle->pointB));

			const auto lengthVector = paddle->pointB - paddle->pointA;
			rectangle.setSize({ length(lengthVector), 2 * paddle->radius });
			// - rotation relative to x-axis
			const float angle = std::atan2(lengthVector.y, lengthVector.x);
			rectangle.setRotation(to_degrees(angle));
			window.draw(rectangle);
		}
	}

	inline static void renderObjects(sf::RenderWindow& window, const std::vector<BlockGrid>& blockGrids)
	{

	}

	inline static void renderObjects(sf::RenderWindow& window, const std::vector<PowerUp>& powerUps)
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

	DebugRenderer& DebugRenderer::get() noexcept
	{
		static DebugRenderer inst;
		return inst;
	}

	template<> void DebugRenderer::registerObject<Ball>(const Ball& object) noexcept;
	template<> void DebugRenderer::registerObject<Paddle>(const Paddle& object) noexcept;
	template<> void DebugRenderer::registerObject<BlockGrid>(const BlockGrid& object) noexcept;
	template<> void DebugRenderer::registerObject<PowerUp>(const PowerUp& object) noexcept;

	template<> void DebugRenderer::removeObject<Ball>(const Ball& object) noexcept;
	template<> void DebugRenderer::removeObject<Paddle>(const Paddle& object) noexcept;
	template<> void DebugRenderer::removeObject<BlockGrid>(const BlockGrid& object) noexcept;
	template<> void DebugRenderer::removeObject<PowerUp>(const PowerUp& object) noexcept;
}