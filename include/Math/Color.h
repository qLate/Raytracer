#pragma once

#include "glm/vec3.hpp"

class Color : public glm::vec3
{
public:
	Color(const float r, const float g, const float b) : glm::vec3(r, g, b) {}
	Color() : Color{0, 0, 0} {}

	static Color white() { return {1, 1, 1}; }
	static Color black() { return {0, 0, 0}; }
	static Color red() { return {1, 0, 0}; }
	static Color green() { return {0, 1, 0}; }
	static Color blue() { return {0, 0, 1}; }
	static Color yellow() { return {1, 1, 0}; }
	static Color cyan() { return {0, 1, 1}; }
	static Color magenta() { return {1, 0, 1}; }
	static Color gray() { return {0.2f, 0.2f, 0.2f}; }

	static Color darkGreen() { return {0, 0.5f, 0}; }
	static Color skyBlue() { return {.529f, .808f, .922f}; }

	float r() const { return x; }
	float g() const { return y; }
	float b() const { return z; }

	uint32_t toColor32() const
	{
		return ((int)(r() * 255) << 16) + ((int)(g() * 255) << 8) + ((int)(b() * 255) << 0);
	}
};
