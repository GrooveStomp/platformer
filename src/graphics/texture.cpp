#include "graphics/texture.h"
#include <SDL_opengl.h>
#include <SDL_image.h>

namespace fob {
    namespace graphics {

namespace TextureUtils
{
    //------------------------------------------------------------------------
    //!
    TextureState CreateTexture(const char *path)
    {
        GLuint texture_id;
        GLenum texture_format;
        GLint num_colors;

        glGenTextures(1, &texture_id);

        SDL_Surface *surface = IMG_Load(path);
        if (!surface)
        {
            printf("Error loading image %s: %s\n", path, IMG_GetError());
            printf("Error loading image %s: %s\n", path, IMG_GetError());
            printf("Error loading image %s: %s\n", path, IMG_GetError());
            printf("Error loading image %s: %s\n", path, IMG_GetError());
        }

        num_colors = surface->format->BytesPerPixel;
        if (4 == num_colors)
        {
            if ((surface->format->Rmask = 0x000000ff))
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        }
        else if (3 == num_colors)
        {
            if ((surface->format->Rmask = 0x000000ff))
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        }
        else
        {
            printf("Error: Unknown format for image %s\n", path);
        }

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            num_colors,
            surface->w,
            surface->h,
            0,
            texture_format,
            GL_UNSIGNED_BYTE,
            surface->pixels
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        TextureState result = TextureState(
            texture_id, surface->w, surface->h
        );

        if (surface)
        {
            SDL_FreeSurface(surface);
        }

        return result;
    }

    //------------------------------------------------------------------------
    //!
    void DeleteTexture(const TextureState &t)
    {
        glDeleteTextures(1, &(t.id));
    }
}

    } // namespace graphics
} // namespace fob
