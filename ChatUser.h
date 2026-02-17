#ifndef CHATUSER_H
#define CHATUSER_H

#include "User.h"
#include <vector>
#include <memory>

class Message;

class ChatUser : public User {
private:
    std::vector<std::shared_ptr<Message>> inbox;

public:
    ChatUser();
    explicit ChatUser(const std::string& u);
    ~ChatUser() override;

    void receiveMessage(const std::shared_ptr<Message>& msg);
    void viewMessages() const;

    void displayProfile() const override;
};

#endif