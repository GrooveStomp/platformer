#ifndef FOB_SYSTEM_QUEUE_NOTIFIER
#define FOB_SYSTEM_QUEUE_NOTIFIER

#include <limits.h>

namespace fob {
    namespace system {

struct QueueState;

struct QueueNotifierState {
    QueueNotifierState(): queueCount(0) {}
    unsigned int queueCount;
    // TODO: AOMAN:
    // If we're storing pointers, then what do we do about loading from disk?
    // Memory locations will change, so the pointers will no longer be valid
    // between saves.
    QueueState* queues[UCHAR_MAX];
};

namespace QueueNotifierUtils {
    void Subscribe(QueueNotifierState& notifier, QueueState& queue);
}

    } // namespace system
} // namespace fob

#endif // FOB_SYSTEM_QUEUE_NOTIFIER
