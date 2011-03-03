#include "world/gamestate.h"

namespace fob {
    namespace world {

namespace GameStateUtils
{
    void Update(GameState &state)
    {
        fob::input::InputState input = fob::input::InputUtils::Update(state);
        state.input = input;
    }

    bool ShouldExit(const GameState &state)
    {
        return (state.input.action == fob::input::InputAction::Quit);
    }
}

    } // namespace world
} // namespace fob
