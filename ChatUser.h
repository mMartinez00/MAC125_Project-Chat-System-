#ifndef CHATUSER_H
#define CHATUSER_H

#include "User.h"
#include "Message.h"
#include <vector>

class ChatUser : public User {
private:
    vector<Message*> inbox;

public:
    ChatUser();
    ChatUser(string u, string p);
    ~ChatUser();

    void receiveMessage(Message* msg);
    void viewMessages() const;

    void displayProfile() const override;
};

#endif