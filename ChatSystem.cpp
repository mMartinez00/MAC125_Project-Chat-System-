#include "ChatSystem.h"
#include "Message.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

static const std::string USERS_FILE = "users.txt";
static const std::string MESSAGES_FILE = "messages.txt";

// ChatSystem::ChatSystem()
//     : nextMessageID(1), timestamp(1) {}
ChatSystem::ChatSystem()
    : nextMessageID(1), timestamp(1) 
{
    // Load users if file exists
    std::ifstream userCheck(USERS_FILE);
    if (userCheck.good()) {
        userCheck.close();
        loadUsers(USERS_FILE);
    }

    // Load messages if file exists
    std::ifstream msgCheck(MESSAGES_FILE);
    if (msgCheck.good()) {
        msgCheck.close();
        loadMessages(MESSAGES_FILE);
    }
}



ChatSystem::~ChatSystem() {}

bool ChatSystem::registerUser(const std::string& username) {
    if (username.empty()) return false;
    if (users.find(username) != users.end()) return false;

    users[username] = std::make_unique<ChatUser>(username);

    saveUsers(USERS_FILE);
    return true;
}

bool ChatSystem::login(const std::string& username) const {
    return users.find(username) != users.end();
}

void ChatSystem::sendMessage(const std::string& sender,
                             const std::string& receiver,
                             const std::string& content) {
    if (sender.empty() || receiver.empty()) {
        throw std::invalid_argument("Sender/receiver cannot be empty.");
    }
    if (content.empty()) {
        throw std::invalid_argument("Message content cannot be empty.");
    }

    auto itSender = users.find(sender);
    auto itReceiver = users.find(receiver);

    if (itSender == users.end()) {
        throw std::runtime_error("Sender not registered: " + sender);
    }
    if (itReceiver == users.end()) {
        throw std::runtime_error("Receiver not registered: " + receiver);
    }

    auto msg = std::make_shared<Message>(
        nextMessageID++,
        sender,
        receiver,
        timestamp++,
        content
    );

    messageLog.push_back(msg);
    itReceiver->second->receiveMessage(msg);

    // save immediately
    saveMessages(MESSAGES_FILE);

    std::cout << "Message sent.\n";
}

void ChatSystem::viewInbox(const std::string& username) const {
    auto it = users.find(username);
    if (it == users.end()) {
        throw std::runtime_error("User not found: " + username);
    }
    it->second->viewMessages();
}

// --- File I/O (minimal) ---

void ChatSystem::loadUsers(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open users file for reading: " + filename);
    }

    std::string name;
    while (std::getline(in, name)) {
        if (!name.empty()) {
            registerUser(name); // ignores duplicates
        }
    }
}

void ChatSystem::saveUsers(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Could not open users file for writing: " + filename);
    }

    for (const auto& pair : users) {
        out << pair.first << '\n';
    }
}

void ChatSystem::saveMessages(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Could not open messages file for writing: " + filename);
    }

    if (messageLog.empty()) {
        out << "No messages.\n";
        return;
    }

    for (const auto& msg : messageLog) {
        out << *msg << '\n';
    }
}

void ChatSystem::loadMessages(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open messages file for reading: " + filename);
    }

    // Write to ttxt file
    std::string line;
    while (std::getline(in, line)) {
   
        if (line.empty()) continue;

      
        std::cout << "[Loaded] " << line << '\n';
    }
}