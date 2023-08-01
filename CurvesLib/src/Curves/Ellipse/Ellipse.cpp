#include "pch.h"
#include "Ellipse.h"

Ellipse::Ellipse(double x, double y, double radius1, double radius2)
    : ICurve(x, y, 0), radius1_(radius1), radius2_(radius2) {}

vec3 Ellipse::GetPoint(double t)
{
    return {this->position_.x + radius1_ * std::cos(t), this->position_.y + radius2_ * std::sin(t), this->position_.z};
}

vec3 Ellipse::GetFirstDerivative(double t)
{
    return {radius1_ * -std::sin(t), radius2_ * std::cos(t), 0};
}
