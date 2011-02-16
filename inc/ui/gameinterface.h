//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "system/interface.h"

namespace fob {
    namespace system {

        class GameInterface : public Interface {
            public:
                GameInterface();
                ~GameInterface();

                virtual void InitGraphics();
                virtual void Draw();

            protected:
        };

    } // namespace system
} // namespace fob

#endif
