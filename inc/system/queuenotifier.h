#ifndef FOB_SYSTEM_QUEUE_NOTIFIER
#define FOB_SYSTEM_QUEUE_NOTIFIER

#include <limits.h>

namespace fob {
    namespace system {

struct QueueState;

/* The Queue Notifier works like Amazon SNS.
 * It is a point of communication to subscribed queues.
 * As far as implementation goes:
 * - QueueNotifier stores a list of queues.  It holds a max of UCHAR_MAX
 *   queues.
 * - QueueNotifier also stores a list of UUIDs for each queue.  This is for
 *   loading from memory.  Pointer locations will be incorrect during
 *   different runs, so we validate first by UUID, then initialize the list
 *   of pointers.
 */
struct QueueNotifierState {
    QueueNotifierState(): queueCount(0) {}
    unsigned int queueCount;
    unsigned char queueUuids[UCHAR_MAX][16];
    QueueState* queues[UCHAR_MAX];
};

namespace QueueNotifierUtils {
    void Subscribe(QueueNotifierState& notifier, QueueState& queue);
}

    } // namespace system
} // namespace fob

#endif // FOB_SYSTEM_QUEUE_NOTIFIER
