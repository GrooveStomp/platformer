//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <string>

namespace fob {
    namespace system {

        class Application {
            public:
                Application(std::string path);
                int Run();

            private:
                int _width;
                int _height;
                Timer _timer;
                bool _running;
                bool _skip_fe;
        };

    } // namespace system
} // namespace fob
#endif
