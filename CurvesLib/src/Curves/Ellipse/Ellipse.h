#pragma once
#include "Curves/ICurve.h"

class CL_API Ellipse : public ICurve
{
public:
    Ellipse(double x, double y, double radius1, double radius2);

    virtual vec3 GetPoint(double t) override;
    virtual vec3 GetFirstDerivative(double t) override;

    [[nodiscard]]
    double GetRadius1() const { return radius1_; }
    [[nodiscard]]
    double GetRadius2() const { return radius2_; }

protected:
    double radius1_;
    double radius2_;
};
