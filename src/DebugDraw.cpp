#include "DebugDraw.h"

static sf::Vector2f toSFMLVertex(b2Vec2 u) noexcept
{
	return { u.x, u.y };
}

static sf::Color toSFMLColour(b2Color c) noexcept
{
	return {
		static_cast<uint8_t>(255 * c.r),
		static_cast<uint8_t>(255 * c.g),
		static_cast<uint8_t>(255 * c.b),
		static_cast<uint8_t>(255 * c.a)
	};
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::VertexArray renderVertices(sf::PrimitiveType::LinesStrip, (size_t)vertexCount + 1);

	for (size_t i = 0; i < renderVertices.getVertexCount(); ++i)
	{
		renderVertices[i].position = toSFMLVertex(vertices[i % vertexCount]);
		renderVertices[i].color = toSFMLColour(color);
	}

	m_window.draw(renderVertices);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::VertexArray renderVertices(sf::PrimitiveType::TriangleFan, (size_t)vertexCount);

	for (size_t i = 0; i < renderVertices.getVertexCount(); ++i)
	{
		renderVertices[i].position = toSFMLVertex(vertices[i]);
		renderVertices[i].color = toSFMLColour(color);
	}

	m_window.draw(renderVertices);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	sf::CircleShape circle;
	const auto sfCentre = toSFMLVertex(center);
	circle.setPosition(sfCentre);
	circle.setOrigin({ radius, radius });
	circle.setRadius(radius);
	circle.setFillColor({ 0, 0, 0, 0 });
	circle.setOutlineColor(toSFMLColour(color));
	circle.setOutlineThickness(-2.0f);
	m_window.draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle;
	const auto sfCentre = toSFMLVertex(center);
	circle.setPosition(sfCentre);
	circle.setOrigin({ radius, radius });
	circle.setRadius(radius);
	circle.setFillColor(toSFMLColour(color));
	m_window.draw(circle);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	const b2Vec2 vertices[] = { p1, p2 };
	DrawPolygon(vertices, 2, color);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{

}