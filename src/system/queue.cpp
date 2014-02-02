#include "system/queue.h"
#include "system/queuenotifier.h"

namespace fob {
    namespace system {

namespace QueueUtils {

    const unsigned int TailPosition(const QueueState& queue)
    {
        const unsigned int tail = (queue.head + queue.messageCount) % UINT_MAX;
        return tail;
    }

    void Send(QueueState& queue, const int message)
    {
        const unsigned int tail = TailPosition(queue);
        if (tail < queue.head)
        {
            queue.messages[tail] = message;
            queue.messageCount += 1;
        }
    }

    void Subscribe(QueueState& queue, QueueNotifierState& notifier)
    {
        QueueNotifierUtils::Subscribe(notifier, queue);
    }

    const int Read(QueueState& queue)
    {
        if (queue.messageCount > 0)
        {
            int message = queue.messages[queue.head];
            queue.head = (queue.head + 1) % UINT_MAX;
            queue.messageCount -= 1;

            return message;
        } else {
            return QueueMessage::NoMessage;
        }
    }

    bool Equal(const QueueState& left, const QueueState& right)
    {
        if (left.messageCount != right.messageCount ||
            left.head != right.head)
        {
            return false;
        }

        for (unsigned int i=0; i < left.messageCount; i++)
        {
            if (left.messages[i] != right.messages[i]) {
                return false;
            }
        }

        return true;
    }
}

    }
}
