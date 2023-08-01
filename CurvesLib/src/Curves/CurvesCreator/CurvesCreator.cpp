#include "pch.h"
#include "CurvesCreator.h"

#include "Curves/Circle/Circle.h"
#include "Curves/Helix/Helix.h"

std::shared_ptr<ICurve> CurvesCreator::CreateCircle(double x, double y, double radius)
{
    if (radius > 0)
        return std::make_shared<Circle>(x, y, radius);

    return nullptr;
}

std::shared_ptr<ICurve> CurvesCreator::CreateEllipse(double x, double y, double radius1, double radius2)
{
    if (radius1 > 0 && radius2 > 0)
        return std::make_shared<Ellipse>(x, y, radius1, radius2);

    return nullptr;
}

std::shared_ptr<ICurve> CurvesCreator::CreateHelix(double x, double y, double z, double radius,
                                                   double step, double start_angle)
{
    if (radius > 0  && step > 0)
        return std::make_shared<Helix>(x, y, z, radius, radius, step, start_angle);

    return nullptr;
}
