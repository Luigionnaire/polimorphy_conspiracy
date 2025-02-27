// Type your code here, or load an example.
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

using uint32_t = unsigned int;
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


class shape_base {
public:
    shape_base() {}
    virtual float Area() = 0;
};

class square : public shape_base
{
public:
    square(float SideInit) : Side(SideInit) {}
    virtual float Area() { return Side * Side; }

private:
    float Side;
};

class triangle : public shape_base
{
public:
    triangle(float BaseInit, float HeightInit) : Base(BaseInit), Height(HeightInit) {}
    virtual float Area() { return 0.5f * Base * Height; }

private:
    float Base, Height;
};

class rectangle : public shape_base
{
public:
    rectangle(float WidthInit, float HeightInit) : Width(WidthInit), Height(HeightInit) {}
    virtual float Area() { return Width * Height; }

private:
    float Width, Height;
};

class circle : public shape_base
{
public:
    circle(float RadiusInit) : Radius(RadiusInit) {}
    virtual float Area() { return M_PI * Radius * Radius; }

private:
    float Radius;
};


float TotalAreaVTBL(int ShapeCount, shape_base** Shapes)
{
    float Accum = 0.0f;
    for (int ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += Shapes[ShapeIndex]->Area();
    }

    return Accum;

}


float DODShapeContainer::calcArea()
{
	float result{ 0.f };
	for (auto& rect : m_rects) { result += rect.height * rect.width; }
	for (auto& square : m_squares) { result += square.side * square.side; }
	for (auto& circle : m_circles) { result += M_PI * circle.radius * circle.radius; }
	for (auto& triangle : m_tris) { result += 0.5f * triangle.base * triangle.height; }
	return result;
}
