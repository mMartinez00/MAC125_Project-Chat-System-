#ifndef CHATSYSTEM_H
#define CHATSYSTEM_H

#include "ChatUser.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

class Message;

class ChatSystem {
private:
    std::unordered_map<std::string, std::unique_ptr<ChatUser>> users;
    std::vector<std::shared_ptr<Message>> messageLog;

    int nextMessageID;
    int timestamp;

public:
    ChatSystem();
    ~ChatSystem();

    // main.cpp expects these:
    bool registerUser(const std::string& username);
    bool login(const std::string& username) const;

    void sendMessage(const std::string& sender,
                     const std::string& receiver,
                     const std::string& content);

    void viewInbox(const std::string& username) const;

    // optional file I/O helpers (simple formats)
    void loadUsers(const std::string& filename);
    void saveUsers(const std::string& filename) const;

    void loadMessages(const std::string& filename);
    void saveMessages(const std::string& filename) const;
};

#endif