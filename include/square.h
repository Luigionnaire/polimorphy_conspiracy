#include "shape_Base.h"

class square : public shape_base
{
public:
    square(float SideInit) : Side(SideInit) {}
    virtual float area() { return Side * Side; }

private:
    float Side;
};