//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/application.h"

int main(int argc, char *argv[])
{
    using namespace fob::system;
    Application game("data/cfg/setup.cfg");
    return game.Run();
}
