//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

namespace fob {
    namespace system {

        class InputManager {
            public:
                static InputManager& Instance();
                void Update();

            private:
                InputManager();
                InputManager(const InputManager&);
                InputManager& operator=(const InputManager&);
                ~InputManager();
        };

    } // namespace system
} // namespace fob

#endif
