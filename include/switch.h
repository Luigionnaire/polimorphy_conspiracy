#define _USE_MATH_DEFINES
#include <math.h>

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