#pragma once
#include "Curves/Ellipse/Ellipse.h"

class CL_API Circle : public Ellipse
{
public:
    Circle(double x, double y, double radius)
        : Ellipse(x, y, radius, radius) {}
};
