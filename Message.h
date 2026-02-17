#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ostream>

class Message {
private:
    int messageID;
    std::string sender;
    std::string receiver;
    int timestamp;
    std::string content;

public:
    Message(int mID,
            const std::string& s,
            const std::string& r,
            int ts,
            const std::string& c);

    virtual ~Message();

    int getMessageID() const;
    const std::string& getSender() const;
    const std::string& getReceiver() const;
    int getTimestamp() const;
    const std::string& getContent() const;

    virtual std::string type() const;
    virtual void print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Message& msg);

#endif