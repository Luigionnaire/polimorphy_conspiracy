#pragma once
#include <vector>

struct DODRectangle
{
	float width{ 0.f };
	float height { 0.f };
};

struct DODSquare
{
	float side{ 0.f };
};

struct DODCircle
{
	float radius{ 0.f };
};

struct DODTriangle
{
	float base{ 0.f };
	float height{ 0.f };
};

class DODShapeContainer
{
public:
	void add(const DODRectangle& rect) { m_types.push_back(std::pair<uint32_t, size_t>(0, m_rects.size()));m_rects.push_back(rect); }
	void add(const DODSquare& square) { m_types.push_back(std::pair<uint32_t, size_t>(1, m_squares.size()));m_squares.push_back(square); }
	void add(const DODCircle& circle) { m_types.push_back(std::pair<uint32_t, size_t>(2, m_circles.size()));m_circles.push_back(circle); }
	void add(const DODTriangle& triangle) { m_types.push_back(std::pair<uint32_t, size_t>(3, m_tris.size()));m_tris.push_back(triangle); }
	float calcArea();
	float calcAreaInOrder();
private:
	std::vector<DODRectangle> m_rects;
	std::vector<DODSquare> m_squares; //dense
	std::vector<DODCircle> m_circles;
	std::vector<DODTriangle> m_tris;
	std::vector<std::pair<uint32_t, size_t>> m_types; // sparse
};
