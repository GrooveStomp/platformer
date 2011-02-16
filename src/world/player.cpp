#include "world/player.h"

#include "world/gamestate.h"

#include <stdio.h>

namespace fob {
    namespace world {

//----------------------------------------------------------------------------
// Private helper functions.
//
namespace PrivateUtils
{
}

//----------------------------------------------------------------------------
// Public utility functions that operate on player state.
//
namespace PlayerUtils
{
    //------------------------------------------------------------------------
    //
    void Update(float dt, GameState &state)
    {
        printf("PlayerUtils::Update()\n");
    }
}

    } // namespace world
} // namespace fob
