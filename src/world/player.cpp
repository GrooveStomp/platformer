#include "world/player.h"

#include "world/gamestate.h"

#include <stdio.h>
#include <SDL_opengl.h>

namespace fob {
    namespace world {

//----------------------------------------------------------------------------
// Public utility functions that operate on player state.
//
namespace PlayerUtils
{
    //------------------------------------------------------------------------
    //
    void Update(PlayerState &player, const GameState &state)
    {
        using namespace fob::math;
        using namespace fob::math::Vec2Utils;

        if (fob::input::InputAction::Left == state.input.action) {
            player.position = Add(player.position, Vec2(-1, 0));
        } else if (fob::input::InputAction::Right == state.input.action) {
            player.position = Add(player.position, Vec2(1, 0));
        } else if (fob::input::InputAction::Down == state.input.action) {
            player.position = Add(player.position, Vec2(0, -1));
        } else if (fob::input::InputAction::Up == state.input.action) {
            player.position = Add(player.position, Vec2(0, 1));
        }
    }

    //------------------------------------------------------------------------
    //
    void Draw(const PlayerState &player, const GameState &state)
    {
        glPushMatrix();
        glScalef(player.width, player.height, 1.0);
        glTranslatef(player.position.x / 100.0, player.position.y / 100.0, 0.0);
        glBegin(GL_QUADS);

        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(-1.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);

        glEnd();
        glPopMatrix();
    }

    //------------------------------------------------------------------------
    //
    void Copy(const PlayerState &other, PlayerState &player)
    {
        player.width = other.width;
        player.height = other.height;
        player.position.x = other.position.x;
        player.position.y = other.position.y;
        player.rotation = other.rotation;
    }
}

    } // namespace world
} // namespace fob
