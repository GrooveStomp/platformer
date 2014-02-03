#include "world/manager/input_manager.h"
#include "input/input.h"
#include "system/queue.h"
#include "system/queuenotifier.h"

namespace fob {
    namespace world {
        namespace manager {

namespace InputManagerUtils
{
    void Update(InputManagerState* const manager)
    {
        using namespace fob::input;
        using namespace fob::system;

        InputUtils::Update(manager->input, manager->messageQueue, manager->messageNotifier);
        QueueUtils::Clear(manager->messageQueue);
    }
}

        } //namespace manager
    } // namespace world
} // namespace fob
