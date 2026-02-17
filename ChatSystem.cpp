#include "ChatSystem.h"
#include "Message.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

ChatSystem::ChatSystem()
    : userASet(false),
      userBSet(false),
      nextMessageID(1),
      timestamp(1) {}

ChatSystem::~ChatSystem() {}

// User setup

void ChatSystem::setUserA(const std::string& username) {
    if (username.empty()) {
        throw std::invalid_argument("User A username cannot be empty.");
    }

    userA = ChatUser(username);
    userASet = true;
}

void ChatSystem::setUserB(const std::string& username) {
    if (username.empty()) {
        throw std::invalid_argument("User B username cannot be empty.");
    }

    if (userASet && username == userA.getUsername()) {
        throw std::invalid_argument("User B cannot have the same username as User A.");
    }

    userB = ChatUser(username);
    userBSet = true;
}

bool ChatSystem::bothUsersReady() const {
    return userASet && userBSet;
}

// Print

void ChatSystem::printAllMessages() const {
    if (messages.empty()) {
        std::cout << "No messages.\n";
        return;
    }

    for (const auto& msg : messages) {
        std::cout << *msg << std::endl; // operator<< from Message
    }
}

// Users I/O

void ChatSystem::loadUsers(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open users file for reading: " + filename);
    }

    std::string usernameA;
    std::string usernameB;

    std::getline(in, usernameA);
    std::getline(in, usernameB);

    if (usernameA.empty() || usernameB.empty()) {
        throw std::runtime_error("Invalid users file format (need 2 lines).");
    }

    setUserA(usernameA);
    setUserB(usernameB);
}

void ChatSystem::saveUsers(const std::string& filename) const {
    if (!bothUsersReady()) {
        throw std::runtime_error("Both users must be set before saving users.");
    }

    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Could not open users file for writing: " + filename);
    }

    out << userA.getUsername() << '\n';
    out << userB.getUsername() << '\n';
}

// Messages I/O (simple log)

void ChatSystem::saveMessages(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Could not open messages file for writing: " + filename);
    }

    if (messages.empty()) {
        out << "No messages.\n";
        return;
    }

    for (const auto& msg : messages) {
        out << *msg << '\n'; // uses Message::operator<<
    }
}

void ChatSystem::loadMessages(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open messages file for reading: " + filename);
    }

    // Since you're keeping it simple and not reconstructing objects:
    messages.clear();

    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << '\n';
    }
}