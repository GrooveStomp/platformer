//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/unique.h"

namespace fob {
    namespace system {

        unsigned int Unique::_id = 0;

        Unique& Unique::Instance() {
            static Unique singleton;
            return singleton;
        }

        unsigned int Unique::Id() {
            // Ensure id is not zero.
            ++_id;
            if (!_id) {
                ++_id;
            }
            return _id;
        }

        Unique::Unique() {
        }

        Unique::Unique(const Unique&) {
        }

        Unique& Unique::operator=(const Unique&) {
            return *this;
        }

    } // namespace system
} // namespace fob
