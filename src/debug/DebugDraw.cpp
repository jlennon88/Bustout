#include "DebugDraw.h"

#include "maths.h"
#include "game/collision.h"

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
			circle.setPosition(capsule->position + sf::Vector2f(capsule->halfLength, 0.0f));
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
		sf::RectangleShape rectangle;
		rectangle.setOutlineThickness(-0.005f);
		rectangle.setFillColor(fillColour);
		rectangle.setOutlineColor(outlineColour);

		for (const auto rect : rects)
		{
			rectangle.setPosition(rect->topLeft);
			rectangle.setSize({ rect->widthHeight.x, -rect->widthHeight.y });
			window.draw(rectangle);
		}
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

	void drawLine(sf::RenderTarget& target, const Line& line, const sf::Color& colour)
	{
		sf::VertexArray vertices(sf::PrimitiveType::Lines, 2);
		vertices[0] = { line.p0, colour, {} };
		vertices[1] = { line.p1, colour, {} };

		target.draw(vertices);
	}

	void debugCircleRectCollision(sf::RenderTarget& target, const bustout::Circle& circle, const bustout::Rectangle& rect)
	{
		const auto collisionData = bustout::testCollision_CircleRect(circle, rect);
		if (collisionData.has_value())
		{
			const auto blockMid = rect.topLeft + sf::Vector2f{ 0.5f * rect.widthHeight.x, -0.5f * rect.widthHeight.y };
			const bustout::Line mouseToBlock = { circle.position, blockMid };
			sf::CircleShape blockMidDot;
			blockMidDot.setPosition(blockMid);
			blockMidDot.setFillColor(sf::Color::Green);
			blockMidDot.setRadius(0.01f);
			blockMidDot.setOrigin(0.01f, 0.01f);
			target.draw(blockMidDot);
			bustout::drawLine(target, mouseToBlock, sf::Color::Magenta);
			for (const auto edge : bustout::getEdges(rect))
			{
				if (testCollision_LineLine(mouseToBlock, edge))
				{
					const auto normal = bustout::normalise(bustout::cross(1.0f, edge.p1 - edge.p0));
					const auto edgeMidPoint = 0.5f * (edge.p0 + edge.p1);
					const auto circleToEdgeDist = bustout::abs(bustout::dot(normal, circle.position - edgeMidPoint));
					const auto boxToEdgeDist = bustout::abs(bustout::dot(normal, edgeMidPoint - blockMid));
					const auto radSum = circle.radius + 0.5f * bustout::abs(bustout::dot(normal, rect.widthHeight));
					const auto delta = bustout::clamp_ge_zero(radSum - (boxToEdgeDist + circleToEdgeDist));
					bustout::drawLine(target, { edgeMidPoint, edgeMidPoint + 0.03f * normal }, sf::Color::Red);
					bustout::drawLine(target, edge, sf::Color::Red);
				}
				else
					bustout::drawLine(target, edge, sf::Color::Cyan);
			}

			const float colDotRad = 0.01f;
			sf::CircleShape colDot;
			colDot.setRadius(colDotRad);
			colDot.setPosition(collisionData.value());
			colDot.setOrigin(colDotRad, colDotRad);
			colDot.setFillColor(sf::Color::Red);
			target.draw(colDot);
		}
	}
}