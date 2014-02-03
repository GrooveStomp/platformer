#include "system/queuenotifier.h"
#include "system/queue.h"

#include <string.h>

namespace fob {
    namespace system {

namespace QueueNotifierUtils {

    bool AlreadySubscribed(const QueueNotifierState* const notifier, const QueueState* queue)
    {
        for (unsigned int i=0; i < notifier->queueCount; i++)
        {
            if (QueueUtils::Equal(notifier->queues[i], queue))
            {
                return true;
            }
        }
        return false;
    }

    void Subscribe(QueueNotifierState* const notifier, QueueState* const queue)
    {
        if (AlreadySubscribed(notifier, queue)) {
            return;
        }

        if (notifier->queueCount >= QUEUE_SIZE) {
            return;
        }

        notifier->queues[notifier->queueCount] = queue;
        strncpy((char *)(notifier->queueUuids[notifier->queueCount]), (char *)(queue->uuid), UUID_SIZE);
        notifier->queueCount++;
    }

    void Send(const QueueNotifierState* const notifier, const int message)
    {
        for (unsigned int i=0; i < notifier->queueCount; i++)
        {
            QueueUtils::Send(notifier->queues[i], message);
        }
    }

    void Name(QueueNotifierState* const notifier, const char* const name)
    {
        strncpy((char*)notifier->name, name, sizeof(name));
    }
}

    } // namespace system
} // namespace fob
