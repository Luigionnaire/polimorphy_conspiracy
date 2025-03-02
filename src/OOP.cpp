#include <array>
#include <iostream>
#include "timer.h"
#include "switch.h"
#include "triangle.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "DODShapes.h"
#include "structOfArrays.h"
#include "arrayOfStructs.h"



int main()
{
    const int arraySize = 10000;
    // Generate data
    int data[arraySize];

    for (size_t c = 0; c < arraySize; ++c)
        data[c] = std::rand();

    {
        Timer timer("Unsorted array", arraySize);
        int sum = 0;
        for (size_t i = 0; i < arraySize; ++i)
        {
            if (data[i] > arraySize / 2) { sum += data[i]; }
        }
    }

    std::sort(data, data + arraySize);
    {
        Timer timer("Sorted array", arraySize);
        int sum = 0;
        for (size_t i = 0; i < arraySize; ++i)
        {
            if(data[i] > arraySize/2){ sum += data[i]; }
        }
    }





    static const int shapeCount = 50000;
    std::vector<shape_base*> shapes(shapeCount);
    std::vector<shape_union> shapeArray(shapeCount);
    DODShapeContainer* DODShapes = new DODShapeContainer;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < shapeCount; ++i) {
        int shapeType = std::rand() % 4;
        float dim1 = 1.0f + (static_cast<float>(std::rand() % 100) / 10.f);
        float dim2 = 1.0f + (static_cast<float>(std::rand() % 100) / 10.f);

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

        // DOD
        switch (shapeType) {
        case 0: DODShapes->add(DODSquare(dim1)); break;
        case 1: DODShapes->add(DODRectangle(dim1, dim2)); break;
        case 2: DODShapes->add(DODTriangle(dim1, dim2)); break;
        case 3: DODShapes->add(DODCircle(dim1)); break;
        }
    }

    float VtblTotal{ 0.0f };
    {
        Timer timer("Polymorphism", shapeCount);
        
        for (size_t ShapeIndex = 0; ShapeIndex < shapeCount; ++ShapeIndex)
        {
            VtblTotal += shapes[ShapeIndex]->area();
        }
    }

    // Time area calculation with switch-based 
    float totalAreaNoPoly = 0.0f;
    {
        Timer timer("Non-Poly Switch", shapeCount);

        for (size_t i = 0; i < shapeCount; ++i) {
            totalAreaNoPoly += GetAreaSwitch(shapeArray[i]);
        }
    }
    // Time area calculation with DOD in order
    float totalAreaDODinOrder = 0.0f;
    {
        Timer timer("DOD ordered", shapeCount);

        totalAreaDODinOrder = DODShapes->calcAreaInOrder();
    }

    // Time area calculation with DOD
    float totalAreaDOD = 0.0f;
    {
        Timer timer("Data oriented", shapeCount);

        totalAreaDOD = DODShapes->calcArea();
    }

    std::cout << "Polymorphism" << " total area: \t" << VtblTotal << std::endl;
    std::cout << "Non-Poly Switch" << " total area: \t" << totalAreaNoPoly << std::endl;
    std::cout << "DOD ordered" << " total area: \t" << totalAreaDODinOrder << std::endl;
    std::cout << "Data oriented" << " total area: \t" << totalAreaDOD << std::endl;
    // Clean up memory
    for (int i = 0; i < shapeCount; ++i) {
        delete shapes[i];
    }

    int numParticles = 10000000;
    particlesSoA sOa(numParticles);
    std::vector<Particle> aOs(numParticles);

    {
        Timer timer("Struct of arrays", numParticles);
        processSoA(sOa);
    }

    {
        Timer timer("Array of structs", numParticles);
        processAoS(aOs);
    }

    system("pause");

    return 0;
}

