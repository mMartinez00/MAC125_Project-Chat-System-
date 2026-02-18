#include <iostream>
#include <string>
#include <exception>
#include "ChatSystem.h"

using namespace std;

static void clearBadInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {

    ChatSystem system;

    try {
        system.loadUsers("users.txt");
    } catch (const exception& e) {
        cout << "No existing users file found.\n";
    }
    
    int choice;

    while (true) {

        cout << "\n=== CHAT SYSTEM ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "4. Load & Display Users\n";
        cout << "Choice: ";

        cin >> choice;

        if(cin.fail()) {
            clearBadInput();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

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

                try {
                    system.displayUserProfile(username);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << '\n';
                }


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
            try {
                system.saveUsers("users.txt");
                system.saveMessages("messages.txt");
                cout << "Data saved successfully.\n";
            } catch(const exception& e) {
                cout << "Error saving data: " << e.what() << "\n";
            }

            cout << "Exiting program...\n";
            break;
        }

        else if (choice == 4) {
            try {
                system.loadUsers("users.txt");
                system.printUsers();
            } catch (const exception& e) {
                cout << "Error: " << e.what() << '\n';
            } 
        } else {
            cout << "Invalid opttion. Choose 1-4.\n";
        }
    }

    return 0;
}