#ifndef FOB_WORLD_MANAGER_INPUT_MANAGER_H
#define FOB_WORLD_MANAGER_INPUT_MANAGER_H

namespace fob {

    namespace input {
        struct InputState;
    }

    namespace system {
        struct QueueState;
        struct QueueNotifierState;
    }

    namespace world {
        namespace manager {

struct InputManagerState
{
    InputManagerState() {}
    fob::input::InputState* input;
    fob::system::QueueState* readQueue;
    fob::system::QueueNotifierState* writeQueue;
};

namespace InputManagerUtils
{
    void Update(InputManagerState& manager);
}

        } // namespace manager
    } // namespace world
} // namespace fob

#endif // FOB_WORLD_MANAGER_INPUT_MANAGER_H
