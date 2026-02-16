#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User();
    User(string u, string p);
    virtual ~User();

    string getUsername() const;
    bool checkPassword(const string& p) const;

    virtual void displayProfile() const;

    bool operator==(const User& other) const;
    friend ostream& operator<<(ostream& out, const User& user);
};

#endif