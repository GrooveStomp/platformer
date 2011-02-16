#include "math/vec2.h"
#include <math.h>

namespace fob {
    namespace math {

//----------------------------------------------------------------------------
//
namespace Vec2Utils
{
    Vec2 Add(const Vec2 &l, const Vec2 &r)
    {
        float x = l.x + r.x;
        float y = l.y + r.y;
        return Vec2(x, y);
    }

    Vec2 Subtract(const Vec2 &minuend, const Vec2 &subtrahend)
    {
        float x = minuend.x - subtrahend.x;
        float y = minuend.y - subtrahend.y;
        return Vec2(x, y);
    }

    Vec2 Multiply(const Vec2 &v, const float amount)
    {
        return Vec2(v.x * amount, v.y * amount);
    }

    Vec2 Divide(const Vec2 &v, const float amount)
    {
        return Vec2(v.x / amount, v.y / amount);
    }

    float DotProduct(const Vec2 &l, const Vec2 &r)
    {
        return l.x * r.x + l.y * r.y;
    }

    bool Equal(const Vec2 &l, const Vec2 &r)
    {
        return (l.x == r.x && l.y == r.y);
    }

    float Length(const Vec2 &v)
    {
        return sqrtf(v.x * v.x + v.y * v.y);
    }

    Vec2 Normalize(const Vec2 &v)
    {
        float l = 1.0 / Length(v);
        return Vec2(v.x * l, v.y * l);
    }
}

    } // namespace math
} // namespace fob
