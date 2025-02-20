#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <chrono>
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
    const int shapeCount = 500000;
    shape_base** shapes = new shape_base * [shapeCount];
    shape_union* shapeArray = new shape_union[shapeCount];
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

    auto start = std::chrono::high_resolution_clock::now();

    float totalArea = TotalAreaVTBL(shapeCount, shapes);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Total area of "<< shapeCount << " shapes: " << totalArea << std::endl;
    std::cout << "Time taken to calculate areas: " << duration.count() << " ns\n";
    std::cout << "Time taken per shape: " << duration.count()/shapeCount << " ns\n";


    // Time area calculation with switch-based 
    auto startNoPoly = std::chrono::high_resolution_clock::now();
    float totalAreaNoPoly = 0.0f;
    for (int i = 0; i < shapeCount; ++i) {
        totalAreaNoPoly += GetAreaSwitch(shapeArray[i]);
    }
    auto endNoPoly = std::chrono::high_resolution_clock::now();
    auto durationNoPoly = std::chrono::duration_cast<std::chrono::nanoseconds>(endNoPoly - startNoPoly);

    std::cout << "Time taken (non-poly): " << durationNoPoly.count() << " ns\n";
    std::cout << "Total area (non-poly): " << totalAreaNoPoly << "\n";
    std::cout << "Time taken per shape (non-poly): " << durationNoPoly.count()/shapeCount << " ns\n";

    // Clean up memory
    for (int i = 0; i < shapeCount; ++i) {
        delete shapes[i];
    }
    delete[] shapes;

    system("pause");

    return 0;
}

