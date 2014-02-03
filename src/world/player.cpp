#include "world/player.h"
#include "world/gamestate.h"
#include "system/queue.h"
#include "system/queuenotifier.h"
#include "input/input.h"

#include <stdio.h>
#include <SDL_opengl.h>

namespace fob {
    namespace world {

namespace PlayerUtils {

    void HandleEvent(PlayerState* const player, const int event)
    {
        using namespace fob::math;
        using namespace fob::math::Vec2Utils;
        using namespace fob::system;

        if (fob::input::InputAction::Left == event) {
            player->position = Add(player->position, Left());
        }
        else if (fob::input::InputAction::Right == event) {
            player->position = Add(player->position, Right());
        }
        else if (fob::input::InputAction::Down == event) {
            player->position = Add(player->position, Down());
        }
        else if (fob::input::InputAction::Up == event) {
            player->position = Add(player->position, Up());
        }

    }

    void Update(PlayerState* const player, const fob::system::QueueState* const messageQueue, fob::system::QueueNotifierState* const messageNotifier)
    {
        using namespace fob::math;
        using namespace fob::math::Vec2Utils;

        for (unsigned int i=0; i < messageQueue->messageCount; i++)
        {
            HandleEvent(player, messageQueue->messages[i]);
        }
    }

    void Draw(const PlayerState* const player, const GameState* const state)
    {
        glPushMatrix();
        glScalef(player->width, player->height, 1.0);
        glTranslatef(player->position.x / 100.0, player->position.y / 100.0, 0.0);
        glBegin(GL_QUADS);

        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(-1.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);

        glEnd();
        glPopMatrix();
    }

    void Copy(const PlayerState* const other, PlayerState* const player)
    {
        player->width = other->width;
        player->height = other->height;
        player->position.x = other->position.x;
        player->position.y = other->position.y;
        player->rotation = other->rotation;
    }

} // namespace PlayerUtils

    } // namespace world
} // namespace fob
