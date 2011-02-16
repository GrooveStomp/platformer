//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef INTERFACE_H
#define INTERFACE_H

#include "system/messagequeue.h"
#include "system/unique.h"

namespace fob {
    namespace interface {

        class Interface {
            public:
                Interface(const char * path) {};
                virtual ~Interface() {};
                virtual void Update() = 0;
                virtual void Draw() = 0;
                virtual void HandleMessage(fob::system::Message &msg) = 0;
                virtual void InitGraphics() = 0;
                virtual void Pause() = 0;
                virtual void UnPause() = 0;
                virtual bool PauseEnabled() = 0;

            protected:
                int _width;
                int _height;
                float _clear_color[4];
                unsigned int _id;
        };

    } // namespace interface
} // namespace fob

#endif
