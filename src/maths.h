#pragma once

#pragma warning(push,0)
#include <SFML/System.hpp>
#pragma warning(pop)

#include <limits>

namespace bustout
{
	constexpr float PI = 3.14159265359f;
	constexpr float Epsilon = 1 / static_cast<float>(std::numeric_limits<uint16_t>::max());

	constexpr float to_radians(float theta) noexcept { return theta * (PI / 180.0f); }
	constexpr float to_degrees(float theta) noexcept { return theta * (180.0f / PI); }

	template<typename T>
	constexpr T min(T a, T b) noexcept { return a < b ? a : b; }
	template<typename T>
	constexpr T max(T a, T b) noexcept { return a < b ? b : a; }
	template<typename T>
	constexpr T clamp(T x, T xMin, T xMax) noexcept { return min(xMax, max(xMin, x)); }

	template<typename T>
	constexpr float clamp_ge_zero(T x) noexcept { return max<T>(x, 0); }
	template<typename T>
	constexpr float clamp_le_zero(T x) noexcept { return min<T>(x, 0); }

	template<typename T>
	constexpr T abs(T x) noexcept { return x < 0 ? -x : x; }

	template<typename T>
	constexpr int sgn(T val) noexcept { return (val > 0) - (val < 0); }

	// linear interpolation between a and b, t should be in [0, 1]
	constexpr float lerp(float t, float a, float b) noexcept
	{
		return t * (b - a) + a;
	}

	// linear interpolation between a and b, t should be in [0, 1]
	inline sf::Vector2f lerp(float t, const sf::Vector2f& a, const sf::Vector2f& b) noexcept
	{
		return { lerp(t, a.x, b.x), lerp(t, a.y, b.y) };
	}

	// smoothly interpolate between 0 and 1
	// t must be within the interval [0, 1] for correct results
	constexpr float smoothStart(float t) noexcept
	{
		return t * t * (3 - 2 * t);
	}

	// smoothly interpolate between 0 and 1
	//  returns 0 for < t a, [0, 1] for t in [a, b], and 1 for t > b
	// b > a for correct results
	constexpr float smoothStart(float t, float a, float b) noexcept
	{
		return smoothStart(clamp((t - a) / (b - a), 0.0f, 1.0f));
	}

	constexpr float smoothStop(float t, float a, float b) noexcept
	{
		return 1.0f - smoothStart(t, a, b);
	}

	inline float dot(const sf::Vector2f& u, const sf::Vector2f& v) noexcept
	{
		return u.x * v.x + u.y * v.y;
	}

	// the '2D cross product' treats the two 2D vectors as if they are
	// both 3D vectors with a 0 z-component, returning the z-component
	// of the resulting 3D vector (the only non-zero component)
	inline float cross(const sf::Vector2f& u, const sf::Vector2f& v) noexcept
	{
		return u.x * v.y - u.y * v.x;
	}

	// 'cross-product' between out-of-plane vector and in-plane vector
	inline sf::Vector2f cross(float z, const sf::Vector2f& xy) noexcept
	{
		return { -z * xy.y, z * xy.x };
	}
	// 'cross-product' between in-plane vector and out-of-plane vector
	inline const sf::Vector2f& cross(const sf::Vector2f& xy, float z) noexcept
	{
		return { z * xy.y, -z * xy.x };
	}

	// simple helper function
	inline bool sameDirection(const sf::Vector2f& u, const sf::Vector2f& v) noexcept
	{
		return dot(u, v) > 0;
	}

	// returns the squared length of the provided vector
	inline float length2(const sf::Vector2f& v) noexcept
	{
		return dot(v, v);
	}

	inline float length(const sf::Vector2f& v) noexcept
	{
		return std::sqrt(length2(v));
	}

	inline sf::Vector2f normalise(const sf::Vector2f& v) noexcept
	{
		return v * (1 / length(v));
	}

	// reflect v across the n - n should be normalised
	inline sf::Vector2f reflect(const sf::Vector2f& v, const sf::Vector2f& n) noexcept
	{
		return v - 2 * dot(n, v) * n;
	}

	constexpr bool isApprox(float x, float y) { return abs(x - y) < Epsilon; }

	constexpr bool isZero(float x) { return abs(x) < Epsilon; }
}