#include "graphics/font.h"
#include "graphics/texture.h"

namespace fob {
    namespace graphics {

namespace FontUtils
{
    //------------------------------------------------------------------------
    // Private Font utility functions.
    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    // Global mapping so we can index into our texture.
    //
    const static char kCharMap[78] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
        'R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h',
        'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y',
        'z','0','1','2','3','4','5','6','7','8','9','?','(',')',',','.',';',
        '=','/','\\','-','+','*','!','[',']'
    };

    //------------------------------------------------------------------------
    // Get the char index so we can access it from our texture.
    //
    int GetCharNum(const char c)
    {
        for (int i=0; i < 78; i++)
        {
            if (c == kCharMap[i])
            {
                return i;
            }
        }

        return -1;
    }

    //------------------------------------------------------------------------
    // Get the x-coordinate of our character out of the texture.
    //
    float GetFontXCoord(const char c, float texture_width)
    {
        if (c == ' ')
            return 0;
        int pos = GetCharNum(c);
        if (pos < 0)
            return 0;
        return (pos % 13) * texture_width;
    }

    //------------------------------------------------------------------------
    // Get the y-coordinate of our character out of the texture.
    //
    float GetFontYCoord(const char c, float texture_height)
    {
        if (c == ' ')
            return 0;
        int pos = GetCharNum(c);
        if (pos < 0)
            return 0;
        return (pos / 13) * texture_height;
    }

    //------------------------------------------------------------------------
    //
    float GetFontWidth(const char c, float texture_width)
    {
        if (c == ' ')
            return 0.01;
        return texture_width;
    }

    //------------------------------------------------------------------------
    //
    float GetFontHeight(const char c, float texture_height)
    {
        if (c == ' ')
            return 0.01;
        return texture_height;
    }

    //------------------------------------------------------------------------
    // Utility function.
    // This is called repeatedly by Draw().
    //
    void DrawGlyph(const char c, const int offset, const TextureState &t)
    {
        float x = GetFontXCoord(c, t.width);
        float y = GetFontYCoord(c, t.height);
        float w = GetFontWidth(c, t.width);
        float h = GetFontHeight(c, t.height);

        glTexCoord2f(x,   y);   glVertex3f(offset * i * cw,      0 + ch, 0);
        glTexCoord2f(x,   y+h); glVertex3f(offset * i * cw,      0,      0);
        glTexCoord2f(x+w, y+h); glVertex3f(offset * i * cw + cw, 0,      0);
        glTexCoord2f(x+w, y);   glVertex3f(offset * i * cw + cw, 0 + ch, 0);
    }


    //------------------------------------------------------------------------
    // Public Font utility functions.
    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    //! Draw the specified text using the given FontState and TextureState.
    //!
    void Draw(const char *text, const FontState &f, const TextureState &t)
    {
        glBindTexture(GL_TEXTURE_2D, t.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(f.position.x, f.position.y, 0);

        float char_width = 0.666666 * f.size;
        float ch = t.scale;
        float cw = (ch / t.size) * char_width;

        glBegin(GL_QUADS);
        glColor4f(f.color.r, f.color.g, f.color.b, f.color.a);

        if (FontAlign::Left == f.align)
        {
            for (int i=0; i < strlen(str); ++i)
            {
                DrawGlyph(str[i], i, t);
            }
        }
        else if (FontAlign::Center == f.align)
        {
            int half = strlen(str) / 2;
            for (int i=0; i < strlen(str); ++i)
            {
                DrawGlyph(str[i], -(half - i), t);
            }
        }
        else if (FontAlign::Right == f.align)
        {
            int size = strlen(str) - 1;
            for (int i=0; i < strlen(str); ++i)
            {
                DrawGlyph(str[i], -(size - i) - 1, t);
            }
        }

        glEnd();
        glPopMatrix();
    }
}

    } // namespace graphics
} // namespace fob
