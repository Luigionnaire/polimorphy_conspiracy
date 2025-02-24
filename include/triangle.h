#include "shape_Base.h"

class triangle : public shape_base
{
public:
    triangle(float BaseInit, float HeightInit) : Base(BaseInit), Height(HeightInit) {}
    virtual float Area() { return 0.5f * Base * Height; }

private:
    float Base, Height;
};