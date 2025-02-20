#define _USE_MATH_DEFINES

#include <array>
#include <math.h>
#include <iostream>
#include "timer.h"

class shape_base
{
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

class rectangle : public shape_base
{
public:
    rectangle(float WidthInit, float HeightInit) : Width(WidthInit), Height(HeightInit) {}
    virtual float Area() { return Width * Height; }

private:
    float Width, Height;
};

class triangle : public shape_base
{
public:
    triangle(float BaseInit, float HeightInit) : Base(BaseInit), Height(HeightInit) {}
    virtual float Area() { return 0.5f * Base * Height; }

private:
    float Base, Height;
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

// NO POLY
enum shape_type : int
{
    Shape_Square,
    Shape_Rectangle,
    Shape_Triangle,
    Shape_Circle,

    Shape_Count,
};

struct shape_union
{
    shape_type Type;
    float Width;
    float Height;
};

float GetAreaSwitch(shape_union Shape)
{
    float Result = 0.0f;

    switch (Shape.Type)
    {
    case Shape_Square: { Result = Shape.Width * Shape.Width; } break;
    case Shape_Rectangle: { Result = Shape.Width * Shape.Height; } break;
    case Shape_Triangle: { Result = 0.5f * Shape.Width * Shape.Height; } break;
    case Shape_Circle: { Result = M_PI * Shape.Width * Shape.Width; } break;

    case Shape_Count: {} break;
    }

    return Result;
}


int main()
{
    static const int shapeCount = 500000;
    std::vector<shape_base*> shapes(shapeCount);
    std::vector<shape_union> shapeArray(shapeCount);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < shapeCount; ++i) {
        int shapeType = std::rand() % 4;
        float dim1 = 1.0f + static_cast<float>(std::rand() % 100);
        float dim2 = 1.0f + static_cast<float>(std::rand() % 100);

        switch (shapeType) {
        case 0: shapes[i] = new square(dim1); break;
        case 1: shapes[i] = new rectangle(dim1, dim2); break;
        case 2: shapes[i] = new triangle(dim1, dim2); break;
        case 3: shapes[i] = new circle(dim1); break;
        }

        // Non-polymorphic shapes
        shapeArray[i].Type = static_cast<shape_type>(shapeType);
        shapeArray[i].Width = dim1;
        shapeArray[i].Height = dim2;
    }

    float VtblTotal{ 0.0f };
    {
        Timer timer("Polymorphic VTable", shapeCount);
        
        for (int ShapeIndex = 0; ShapeIndex < shapeCount; ++ShapeIndex)
        {
            VtblTotal += shapes[ShapeIndex]->Area();
        }
    }

    // Time area calculation with switch-based 
    float totalAreaNoPoly = 0.0f;
    {
        Timer timer("Non-Polymorphic switch", shapeCount);

        for (int i = 0; i < shapeCount; ++i) {
            totalAreaNoPoly += GetAreaSwitch(shapeArray[i]);
        }
    }

    std::cout << "total: " << VtblTotal << std::endl;
    std::cout << "total: " << totalAreaNoPoly << std::endl;
    // Clean up memory
    for (int i = 0; i < shapeCount; ++i) {
        delete shapes[i];
    }

    system("pause");

    return 0;
}

