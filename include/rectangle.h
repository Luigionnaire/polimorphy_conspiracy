#include "shape_Base.h"

class rectangle : public shape_base
{
public:
    rectangle(float WidthInit, float HeightInit) : Width(WidthInit), Height(HeightInit) {}
    virtual float area() { return Width * Height; }

private:
    float Width, Height;
};