#ifndef FOB_SYSTEM_QUEUE
#define FOB_SYSTEM_QUEUE

#include <limits.h>

namespace fob {
    namespace system {

/*
 * Each game component will have it's own queue that it reads events from.
 *
 * Each Queue subscribes to a QueueNotifier.
 * Each QueueNotifier broadcasts messages to all of it's subscribers.
 */

struct QueueNotifierState;

namespace QueueMessage
{
    enum Enum
    {
        NoMessage = -666
    };
}

struct QueueState {
    QueueState(): messageCount(0), head(0) {}
    unsigned int messageCount;
    unsigned int head;
    int messages[UINT_MAX];
};

namespace QueueUtils {
    void Send(QueueState& queue, const int message);
    void Subscribe(QueueState& queue, QueueNotifierState& notifier);
    const int Read(QueueState& queue);
    bool Equal(const QueueState& left, const QueueState& right);
}

    }
}

#endif // FOB_SYSTEM_QUEUE
