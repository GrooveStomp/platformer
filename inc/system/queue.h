#ifndef FOB_SYSTEM_QUEUE
#define FOB_SYSTEM_QUEUE

#include "system/types.h"

#include <uuid/uuid.h>


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
    unsigned char uuid[UUID_SIZE];
    unsigned int messageCount;
    unsigned int head;
    int messages[QUEUE_SIZE];
    char name[MAX_NAME_SIZE];
};

namespace QueueUtils {
    void Init(QueueState* const queue);
    void Send(QueueState* const queue, const int message);
    void Subscribe(QueueState* const queue, QueueNotifierState* const notifier);
    const int Read(QueueState* const queue);
    bool Equal(const QueueState* const left, const QueueState* const right);
    void Clear(QueueState* const queue);
    void Name(QueueState* const queue, const char* const name);
}

    }
}

#endif // FOB_SYSTEM_QUEUE
