#pragma once
#include <pch.h>

#include "Curves/ICurve.h"

class CL_API CurvesCreator
{
public:
    CurvesCreator() = delete;

    static std::shared_ptr<ICurve> CreateCircle(double x, double y, double radius);
    static std::shared_ptr<ICurve> CreateEllipse(double x, double y, double radius1, double radius2);
    static std::shared_ptr<ICurve> CreateHelix(double x, double y, double z, double radius,
                                               double step, double start_angle = 0);
};
