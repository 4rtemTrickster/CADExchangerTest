#include "pch.h"
#include "Helix.h"

Helix::Helix(double x, double y, double z, double radius1, double radius2, double step, double start_angle)
    : ICurve(x, y, z), radius1_(radius1), radius2_(radius2), step_(step), start_angle_(start_angle) {}

vec3 Helix::GetPoint(double t)
{
    return {
        this->position_.x + radius1_ * std::cos(t),
        this->position_.y + radius2_ * std::sin(t),
        this->position_.z + (start_angle_ + t) / (M_PI * 2) * step_
    };
}

vec3 Helix::GetFirstDerivative(double t)
{
    return {radius1_ * -std::sin(t), radius2_ * std::cos(t), step_ / (M_PI * 2)};
}
