#ifndef FOB_SYSTEM_QUEUE_NOTIFIER
#define FOB_SYSTEM_QUEUE_NOTIFIER

#include <limits.h>

#include "system/types.h"

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
    unsigned char queueUuids[UCHAR_MAX][UUID_SIZE];
    QueueState* queues[UCHAR_MAX];
    char name[MAX_NAME_SIZE];
};

namespace QueueNotifierUtils {
    void Subscribe(QueueNotifierState* const notifier, QueueState* const queue);
    void Send(const QueueNotifierState* const notifier, const int message);
    void Name(QueueNotifierState* const notifier, const char* const name);
}

    } // namespace system
} // namespace fob

#endif // FOB_SYSTEM_QUEUE_NOTIFIER
