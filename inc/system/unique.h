//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef UNIQUE_H
#define UNIQUE_H

namespace fob {
    namespace system {

        class Unique {
            public:
                static Unique& Instance();
                unsigned int Id();

            private:
                Unique();
                Unique(const Unique&);
                Unique& operator=(const Unique&);

                static unsigned int _id;
        };

    } // namespace system
} // namespace fob

#endif
