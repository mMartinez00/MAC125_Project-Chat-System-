#include "ChatUser.h"
#include "Message.h"
#include <iostream>

ChatUser::ChatUser() : User() {}

ChatUser::ChatUser(const std::string& u) : User(u) {}

ChatUser::~ChatUser() {}

void ChatUser::receiveMessage(const std::shared_ptr<Message>& msg) {
    inbox.push_back(msg);
}

void ChatUser::viewMessages() const {
    if (inbox.empty()) {
        std::cout << "No messages.\n";
        return;
    }

    for (const auto& msg : inbox) {
        std::cout << *msg << '\n';
    }
}

void ChatUser::displayProfile() const {
    std::cout << "Chat User: " << username << '\n';
}