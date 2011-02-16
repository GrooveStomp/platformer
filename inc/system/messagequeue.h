//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <queue>
#include <map>

namespace fob {
    namespace system {

        struct Event {
            typedef int eEventEnum;
            enum {
                GROW,
                SHRINK,
                COLLIDE,
                DIE, // mark an object for deletion
                SHOOT,
                POOP, // create a health icon
                PAUSE,
                EXIT,
                UNPAUSE,
                ACTIVATE,
                START, // start the game
                TOFE, // exit to the front end
                TAKE, // take spacemen
                GIVE, // give spacemen
                CANCEL,
                HIT,
                EXPLODE,
                MATCH_END
            };
        };

        struct Message {
            Message(Event::eEventEnum _event_id, unsigned int recipient_id, unsigned int initiator_id=0);
            Message(const Message &rhs);
            const Message& operator=(const Message &rhs);
            Event::eEventEnum _event_id;
            unsigned int _recipient_id;
            unsigned int _initiator_id;
        };

        class MessageQueue {
            public:
                static MessageQueue& Instance();
                void Broadcast(Message m);
                void Broadcast(Event::eEventEnum event_id, unsigned int recipient_id, unsigned int initiator_id=0);
                Message& Peek();
                void Next();
                bool Empty();

            private:
                MessageQueue();
                MessageQueue(MessageQueue&) {}
                ~MessageQueue() {}
                std::queue<Message> _messages;
        };

    } // namespace system
} // namespace fob

#endif
