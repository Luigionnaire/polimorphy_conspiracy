#include <array>
#include <iostream>
#include "timer.h"
#include "switch.h"
#include "triangle.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"


float TotalAreaVTBL(int ShapeCount, shape_base** Shapes)
{
    float Accum = 0.0f;
    for (int ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += Shapes[ShapeIndex]->Area();
    }

    return Accum;

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

