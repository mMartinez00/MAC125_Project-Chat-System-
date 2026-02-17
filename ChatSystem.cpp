#include "ChatSystem.h"
#include "TextMessage.h"
#include "Message.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace {
    // Simple escaping so content can include tabs/newlines.
    std::string escape(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (char ch : s) {
            if (ch == '\\') out += "\\\\";
            else if (ch == '\t') out += "\\t";
            else if (ch == '\n') out += "\\n";
            else out += ch;
        }
        return out;
    }

    std::string unescape(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '\\' && i + 1 < s.size()) {
                char n = s[i + 1];
                if (n == '\\') { out += '\\'; ++i; }
                else if (n == 't') { out += '\t'; ++i; }
                else if (n == 'n') { out += '\n'; ++i; }
                else out += s[i]; // leave unknown escape as-is
            } else {
                out += s[i];
            }
        }
        return out;
    }
}

ChatSystem::ChatSystem()
    : nextMessageID(1), timestamp(1) {}

ChatSystem::~ChatSystem() {}

bool ChatSystem::registerUser(const std::string& username) {
    if (username.empty()) return false;
    if (users.find(username) != users.end()) return false;

    users[username] = std::make_unique<ChatUser>(username);
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

    auto msg = std::make_shared<TextMessage>(
        nextMessageID++,
        sender,
        receiver,
        timestamp++,
        content
    );

    messageLog.push_back(msg);
    itReceiver->second->receiveMessage(msg);

    std::cout << "Message sent.\n";
}

void ChatSystem::viewInbox(const std::string& username) const {
    auto it = users.find(username);
    if (it == users.end()) {
        throw std::runtime_error("User not found: " + username);
    }
    it->second->viewMessages();
}

// ---------- Users I/O (one username per line) ----------

void ChatSystem::loadUsers(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open users file: " + filename);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            registerUser(line); // ignores duplicates
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

// ---------- Messages I/O (tab-delimited) ----------
// Format per line:
// messageID \t timestamp \t sender \t receiver \t type \t escaped_content

void ChatSystem::saveMessages(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Could not open messages file for writing: " + filename);
    }

    for (const auto& msg : messageLog) {
        out << msg->getMessageID() << '\t'
            << msg->getTimestamp() << '\t'
            << msg->getSender() << '\t'
            << msg->getReceiver() << '\t'
            << msg->type() << '\t'
            << escape(msg->getContent()) << '\n';
    }
}

void ChatSystem::loadMessages(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open messages file: " + filename);
    }

    messageLog.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);

        int id = 0;
        int ts = 0;
        std::string sender, receiver, type, escContent;

        if (!(ss >> id)) continue;
        if (ss.get() != '\t') continue;

        if (!(ss >> ts)) continue;
        if (ss.get() != '\t') continue;

        if (!std::getline(ss, sender, '\t')) continue;
        if (!std::getline(ss, receiver, '\t')) continue;
        if (!std::getline(ss, type, '\t')) continue;
        if (!std::getline(ss, escContent)) escContent = "";

        std::string content = unescape(escContent);

        // Ensure users exist so inbox delivery is possible
        registerUser(sender);
        registerUser(receiver);

        // Rebuild message object (only TEXT supported here)
        auto msg = std::make_shared<TextMessage>(id, sender, receiver, ts, content);
        messageLog.push_back(msg);

        // deliver to receiver inbox (like “replaying” the log)
        users[receiver]->receiveMessage(msg);

        // keep counters sane
        if (id >= nextMessageID) nextMessageID = id + 1;
        if (ts >= timestamp) timestamp = ts + 1;
    }
}