#pragma once
#include <pch.h>

struct CL_API vec3
{
  double x;
  double y;
  double z;

  friend std::ostream& operator << (std::ostream& ostream, const vec3& vec)
  {
    ostream << "{" << vec.x << "," << vec.y << "," << vec.z << "}";
    return ostream;
  }
};
