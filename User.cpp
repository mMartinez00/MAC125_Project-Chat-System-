#include "User.h"

User::User() : username(""), password("") {}
User::User(string u, string p) : username(u), password(p) {}
User::~User() {}

string User::getUsername() const {
    return username;
}

bool User::checkPassword(const string& p) const {
    return password == p;
}

void User::displayProfile() const {
    cout << "Username: " << username << endl;
}

bool User::operator==(const User& other) const {
    return username == other.username;
}

ostream& operator<<(ostream& out, const User& user) {
    out << user.username;
    return out;
}