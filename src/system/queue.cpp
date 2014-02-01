#include "system/queue.h"
#include "system/queuenotifier.h"

namespace fob {
    namespace system {

namespace QueueUtils {

    const unsigned int TailPosition(const QueueState &queue) const
    {
        tail = (queue.head + queue.messageCount) % UINT_MAX;
        return tail;
    }

    void Send(QueueState &queue, const QueueMessage &message)
    {
        tail = TailPosition(queue);
        if (tail < queue.head)
        {
            queue.messages[tail] = message;
            queue.messageCount += 1;
        }
    }

    void Subscribe(const QueueState &queue, QueueNotifier &notifier)
    {
        QueueNotifierUtils::subscribe(notifier, queue);
    }

    const int Read(QueueState &queue)
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
}

    }
}
