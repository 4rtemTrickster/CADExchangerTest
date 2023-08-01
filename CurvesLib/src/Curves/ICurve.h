#pragma once

#include <vec3/vec3.h>

class CL_API ICurve
{
public:
    ICurve(double x, double y, double z) : position_(x, y, z) {}
    virtual ~ICurve() = default;
    
    virtual vec3 GetPoint(double t) = 0;
    virtual vec3 GetFirstDerivative(double t) = 0;

protected:
    vec3 position_;
};