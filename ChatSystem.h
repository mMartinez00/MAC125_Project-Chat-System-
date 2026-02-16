#ifndef CHATSYSTEM_H
#define CHATSYSTEM_H
#include "ChatUser.h"
#include <vector>
#include <memory>
#include <string>

class Message;

class ChatSystem {
    private:
    ChatUser userA; 
    ChatUser userB;

    bool userASet;
    bool userBSet;

    std::vector<std::unique_ptr<Message>> messages;
    
    int nextMessageID;
    int timestamp;  

    public:
    ChatSystem();
    ~ChatSystem();

    void setUserA(const std::string& username);

    void setUserB(const std::string& username);

    bool bothUsersReady() const;

    void printAllMessages() const;

    void loadUsers(const std::string& filename);

    void saveUsers(const std::string& filename) const;

    void loadMessages(const std::string& filename);

    void saveMessages(const std::string& filename) const;
};

#endif