#ifndef FOB_MATH_VEC2_H
#define FOB_MATH_VEC2_H

namespace fob {
    namespace math {

//----------------------------------------------------------------------------
//
struct Vec2
{
    Vec2(const float ix = 0, const float iy = 0): x(ix), y(iy) {}
    float x;
    float y;
};

//----------------------------------------------------------------------------
//
namespace Vec2Utils
{
    Vec2 Add(const Vec2 &l, const Vec2 &r);
    Vec2 Subtract(const Vec2 &minuend, const Vec2 &subtrahend);
    Vec2 Multiply(const Vec2 &v, const float amount);
    Vec2 Divide(const Vec2 &v, const float amount);
    float DotProduct(const Vec2 &l, const Vec2 &r);
    bool Equal(const Vec2 &l, const Vec2 &r);
    float Length(const Vec2 &v);
    Vec2 Normalize(const Vec2 &v);
}

    } // namespace math
} // namespace fob

#endif
