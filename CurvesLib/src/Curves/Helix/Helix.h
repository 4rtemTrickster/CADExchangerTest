#pragma once
#include "Curves/ICurve.h"

class CL_API Helix : public ICurve
{
public:
    Helix(double x, double y, double z, double radius1, double radius2, double step, double start_angle);

    virtual vec3 GetPoint(double t) override;
    virtual vec3 GetFirstDerivative(double t) override;

    [[nodiscard]]
    double GetStep() const { return step_; }

protected:
    double radius1_;
    double radius2_;
    double step_;
    double start_angle_;
};
