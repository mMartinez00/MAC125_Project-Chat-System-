#include "Message.h"
#include <string>   

Message::Message(int mID, int sID, int ts, const std::string& c) : messageID(mID), senderID(sID), timestamp(ts), content(c) { }

Message::~Message(){}

std::string Message::type() const {
    return "TEXT";
}

void Message::print(std::ostream& os) const {
    os << "[ID: " << messageID << " | Sender: " << senderID << " | Time: " << timestamp << "]" << " " << content;
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
    msg.print(os);

    return os;
}