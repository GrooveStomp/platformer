//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <string>

namespace fob {
    namespace system {

        class ObjectManager {
            public:
                virtual void Init(std::string cfg_name) = 0;
                virtual void Update() = 0;
                virtual void HandleMessage(Message &msg) = 0;
                virtual void Draw() = 0;

            protected:
        };
    } // namespace system
} // namespace fob

#endif
