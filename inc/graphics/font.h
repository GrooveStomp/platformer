#ifndef FOB_GRAPHICS_FONT_H
#define FOB_GRAPHICS_FONT_H

#include "math/vec2.h"
#include "graphics/color.h"

namespace fob {
    namespace graphics {

//----------------------------------------------------------------------------
//
namespace FontAlign
{
    enum Enum
    {
        Left,
        Right,
        Center,
        Max
    };
}

//----------------------------------------------------------------------------
//
struct FontState
{
    FontState():
        color(), position(), align(FontAlign::Left), size(11), scale(11) {}
    fob::graphics::Color color;
    fob::math::Vec2 position;
    FontAlign align;
    float scale;
    float size;
};

//----------------------------------------------------------------------------
//
namespace FontUtils
{
    void Draw(const char *text, const FontState &f, const TextureState &t);
}

    } // namespace graphics
} // namespace fob

#endif
