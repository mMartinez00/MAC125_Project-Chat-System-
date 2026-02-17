#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
protected:
    string username;

public:
    User();//default constructor
    User(string u);//paramatized constructor
    virtual ~User();//Destruct runs

    string getUsername() const;

    virtual void displayProfile() const;

    bool operator==(const User& other) const;//operator overloading to compare username
    friend ostream& operator<<(ostream& out, const User& user);
};

#endif