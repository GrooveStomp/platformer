#ifndef FOB_GRAPHICS_TEXTURE_H
#define FOB_GRAPHICS_TEXTURE_H

namespace fob {
    namespace graphics {

//----------------------------------------------------------------------------
//
struct TextureState
{
    TextureState(unsigned int iid = 0, float iwidth = 0, float iheight = 0):
        id(iid), width(iwidth), height(iheight) {}
    unsigned int id;
    float width;
    float height;
};

//----------------------------------------------------------------------------
//
namespace TextureUtils
{
    TextureState CreateTexture(const char *path);
    void DeleteTexture(const TextureState &t);
}


    } // namespace graphics
} // namespace fob

#endif
