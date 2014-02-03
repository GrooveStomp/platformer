#include <string.h>

#include "system/queuenotifier.h"
#include "system/queue.h"

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

        if (notifier->queueCount >= UCHAR_MAX) {
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

}

    } // namespace system
} // namespace fob
