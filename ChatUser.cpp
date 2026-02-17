#include "ChatUser.h"

ChatUser::ChatUser() : User() {}

ChatUser::ChatUser(const std::string& u) : User(u) {}

ChatUser::~ChatUser() {
    for (Message* msg : inbox)
        delete msg;
}

void ChatUser::receiveMessage(Message* msg) {
    inbox.push_back(msg);
}

void ChatUser::viewMessages() const {
    if (inbox.empty()) {
        cout << "No messages.\n";
        return;
    }

    for (const Message* msg : inbox)
        cout << *msg << endl;
}

void ChatUser::displayProfile() const {
    cout << "Chat User: " << username << endl;
}