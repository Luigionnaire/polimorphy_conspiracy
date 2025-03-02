#include "shape_Base.h"
#include <math.h>
class circle : public shape_base
{
public:
    circle(float RadiusInit) : Radius(RadiusInit) {}
    virtual float area() { return M_PI * Radius * Radius; }

private:
    float Radius;
};