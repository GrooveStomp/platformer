namespace fob {

    namespace system {

/*
 * Each game component will have it's own queue that it reads events from.
 *
 * Each Queue subscribes to a QueueNotifier.
 * Each QueueNotifier broadcasts messages to all of it's subscribers.
 */

namespace QueueMessage
{
    enum Enum
    {
        NoMessage = -666;
    }
}

struct QueueState {
    QueueState(): messageCount(0), head(0) {}
    unsigned int messageCount;
    unsigned int head;
    int messages[UINT_MAX];
}

namespace QueueUtils {
    void Send(QueueState &queue, const QueueMessage &message);
    void Subscribe(const QueueState &queue, QueueNotifier &notifier);
    const int Read(QueueState &queue);
}

    }
}
