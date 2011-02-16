#ifndef FOB_GRAPHICS_COLOR_H
#define FOB_GRAPHICS_COLOR_H

namespace fob {
    namespace graphics {

//----------------------------------------------------------------------------
//
struct Color
{
    Color(const float ir = 0, const float ig = 0, const float ib = 0, const float ia = 0):
        r(ir), g(ig), b(ib), a(ia) {}
    float r;
    float g;
    float b;
    float a;
};

//----------------------------------------------------------------------------
//
namespace ColorUtils
{
}

    } // namespace graphics
} // namespace fob

#endif
