//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/messagequeue.h"
#include "system/config.h"

namespace fob {
    namespace system {

        Message::Message(Event::eEventEnum event_id, unsigned int recipient_id, unsigned int initiator_id) {
            _event_id = event_id;
            _recipient_id = recipient_id;
            _initiator_id = initiator_id;
        }

        Message::Message(const Message &rhs) {
            _event_id = rhs._event_id;
            _recipient_id = rhs._recipient_id;
            _initiator_id = rhs._initiator_id;
        }

        const Message& Message::operator=(const Message &rhs) {
            _event_id = rhs._event_id;
            _recipient_id = rhs._recipient_id;
            _initiator_id = rhs._initiator_id;
            return *this;
        }

        MessageQueue& MessageQueue::Instance() {
            static MessageQueue queue;
            return queue;
        }

        MessageQueue::MessageQueue() {
        }

        void MessageQueue::Broadcast(Message m) {
            _messages.push(m);
        }

        void MessageQueue::Broadcast(Event::eEventEnum event_id, unsigned int recipient_id, unsigned int initiator_id) {
            _messages.push( Message(event_id, recipient_id, initiator_id) );
        }

        Message& MessageQueue::Peek() {
            return _messages.front();
        }

        void MessageQueue::Next() {
            _messages.pop();
        }

        bool MessageQueue::Empty() {
            return _messages.empty();
        }

    } // namespace system
} // namespace fob
