#ifndef FOB_INPUT_INPUT_H
#define FOB_INPUT_INPUT_H

#include "system/queue.h"
#include "system/queuenotifier.h"

namespace fob {
    namespace world {
        struct GameState;
    }
    namespace input {

//-----------------------------------------------------------------------------
//
namespace InputAction
{
    enum Enum
    {
        None,
        Jump,
        Left,
        Right,
        Up,
        Down,
        Quit
    };
}

//-----------------------------------------------------------------------------
//
struct InputState
{
    InputState(InputAction::Enum action=InputAction::None):action(action) {}
    InputAction::Enum action;
};

//-----------------------------------------------------------------------------
//
namespace InputUtils
{
    using namespace fob::system;
    void Update(InputState* const input, const QueueState* const messageQueue, QueueNotifierState* const messageNotifier);
}

    } // namespace input
} // namespace fob

#endif
