#include "Message.h"

Message::Message(int mID,
                 const std::string& s,
                 const std::string& r,
                 int ts,
                 const std::string& c)
    : messageID(mID), sender(s), receiver(r), timestamp(ts), content(c) {}

Message::~Message() {}

int Message::getMessageID() const { return messageID; }
const std::string& Message::getSender() const { return sender; }
const std::string& Message::getReceiver() const { return receiver; }
int Message::getTimestamp() const { return timestamp; }
const std::string& Message::getContent() const { return content; }

std::string Message::type() const { return "TEXT"; }

void Message::print(std::ostream& os) const {
    os << "["
       << type()
       << " | ID: " << messageID
       << " | " << sender << " -> " << receiver
       << " | Time: " << timestamp
       << "] " << content;
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
    msg.print(os);
    return os;
}