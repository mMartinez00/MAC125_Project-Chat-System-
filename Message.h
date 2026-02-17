#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <ostream>

class Message {
    private:
        int messageID;
        int senderID;
        int timestamp;
        std::string content;

    public:
        Message(int mID, int sID, int ts, const std::string& c);

        virtual std::string type() const;

        virtual void print(std::ostream&) const;

        int getMessageID() const;

        const std::string& getContent() const;

        virtual ~Message();

};

std::ostream& operator<<(std::ostream&, const Message&);

#endif