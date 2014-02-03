#include "system/queue.h"
#include "system/queuenotifier.h"

#include <uuid/uuid.h>
#include <string.h>

namespace fob {
    namespace system {

namespace QueueUtils {

    const unsigned int TailPosition(const QueueState* const queue)
    {
        const unsigned int tail = (queue->head + queue->messageCount) % QUEUE_SIZE;
        return tail;
    }

    void Init(QueueState* const queue)
    {
        uuid_generate(queue->uuid);
    }

    void Send(QueueState* const queue, const int message)
    {
        const unsigned int tail = TailPosition(queue);
        if (tail < queue->head)
        {
            queue->messages[tail] = message;
            queue->messageCount += 1;
        }
    }

    void Subscribe(QueueState* const queue, QueueNotifierState* const notifier)
    {
        QueueNotifierUtils::Subscribe(notifier, queue);
    }

    const int Read(QueueState* const queue)
    {
        if (queue->messageCount > 0)
        {
            int message = queue->messages[queue->head];
            queue->head = (queue->head + 1) % QUEUE_SIZE;
            queue->messageCount -= 1;

            return message;
        } else {
            return QueueMessage::NoMessage;
        }
    }

    bool Equal(const QueueState* const left, const QueueState* const right)
    {
        if (left->messageCount != right->messageCount ||
            left->head != right->head)
        {
            return false;
        }

        for (unsigned int i=0; i < left->messageCount; i++)
        {
            if (left->messages[i] != right->messages[i]) {
                return false;
            }
        }

        return true;
    }

    void Clear(QueueState* const queue)
    {
        queue->messageCount = 0;
        queue->head = 0;
    }

    void Name(QueueState* const queue, const char* const name)
    {
        strncpy((char*)queue->name, name, sizeof(name));
    }
}

    }
}
