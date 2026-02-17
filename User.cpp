#include "User.h"

User::User() : username("") {}

User::User(string u) : username(u) {}

User::~User() {}

string User::getUsername() const {
    return username;
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