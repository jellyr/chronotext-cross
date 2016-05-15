#pragma once

#include "math/Utils.h"

namespace chr
{
  namespace shape
  {
    class Circle
    {
    public:
      Circle& setRadius(float radius)
      {
        r = radius;
        return *this;
      }

      Circle& setArc(float a1, float a2)
      {
        this->a1 = a1;
        this->a2 = a2;

        return *this;
      }

      Circle& setSegmentLength(float length)
      {
        segmentLength = length;
        return *this;
      }

      std::vector<glm::vec2> get() const
      {
        float aa = fabsf(a2 - a1);
        int n = ceilf(aa * r / segmentLength) + 1;

        std::vector<glm::vec2> output;
        output.reserve(n);

        for (int i = 0; i < n; i++)
        {
          float d = fmin(aa, i * segmentLength / r);
          output.emplace_back(+sinf(a1 - d) * r, -cosf(a1 - d) * r);
        }

        return output;
      }

    protected:
      float r = 1;
      float a1 = 0;
      float a2 = TWO_PI;
      float segmentLength = 8;
    };
  }
}