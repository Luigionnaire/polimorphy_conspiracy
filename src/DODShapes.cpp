#include "DODShapes.h"
#define _USE_MATH_DEFINES
#include <math.h>

float DODShapeContainer::calcArea()
{
	float result{ 0.f };
	for (auto& rect : m_rects) { result += rect.height * rect.width; }
	for (auto& square : m_squares) { result += square.side * square.side; }
	for (auto& circle : m_circles) { result += M_PI * circle.radius * circle.radius; }
	for (auto& triangle : m_tris) { result += 0.5f * triangle.base * triangle.height; }
	return result;
}

float DODShapeContainer::calcAreaInOrder() // causes problem with branch prediction
{
	float result{ 0.f };
	for (auto& [type, idx] : m_types) {
		switch (type) {
		case 0:
		{
			auto& rect = m_rects[idx];
			result += rect.height * rect.width;
		}
			break;
		case 1:
		{
			auto& square = m_squares[idx];
			result += square.side * square.side;
		}
			break;
		case 2:
		{
			auto& circle = m_circles[idx];
			result += M_PI * circle.radius * circle.radius;
		}
			break;
		case 3:
		{
			auto& triangle = m_tris[idx];
			result += 0.5f * triangle.base * triangle.height;
		}
			break;
		}

	}

	return result;
}
