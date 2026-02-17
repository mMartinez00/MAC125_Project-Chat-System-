#include <iostream>
#include <string>
#include "ChatSystem.h"

using namespace std;

int main() {

    ChatSystem system;
    int choice;

    while (true) {

        cout << "\n=== CHAT SYSTEM ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {

            string username;
            cout << "Enter username: ";
            cin >> username;

            if (system.registerUser(username))//bool to check if the username already exist or not
                cout << "User registered successfully!\n";
            else
                cout << "Username already exists.\n";
        }

        else if (choice == 2) {

            string username;
            cout << "Enter username: ";
            cin >> username;

            if (system.login(username)) {

                cout << "Login successful!\n";

                while (true) {

                    cout << "\n1. Send Message\n";
                    cout << "2. View Inbox\n";
                    cout << "3. Logout\n";
                    cout << "Choice: ";

                    int userChoice;
                    cin >> userChoice;

                    if (userChoice == 1) {

                        string receiver;
                        string content;

                        cout << "Enter receiver username: ";
                        cin >> receiver;
                        cin.ignore();

                        cout << "Enter message: ";
                        getline(cin, content);

                        system.sendMessage(username, receiver, content);
                    }

                    else if (userChoice == 2) {
                        system.viewInbox(username);
                    }

                    else if (userChoice == 3) {
                        cout << "Logged out.\n";
                        break;
                    }
                }
            }
            else {
                cout << "User not found.\n";
            }
        }

        else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        }
    }

    return 0;
}