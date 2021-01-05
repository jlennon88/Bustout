#pragma once

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#include <box2d/b2_draw.h>
#pragma warning(pop)

class DebugDraw final : public b2Draw
{
public:
	DebugDraw(sf::RenderWindow& window) : m_window(window) {}

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) final;

	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) final;

	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) final;

	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) final;

	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) final;

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf) final;

	/// Draw a point.
	virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) final;
private:
	sf::RenderWindow& m_window;
};