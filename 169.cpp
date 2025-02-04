#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void createAccount() {
    string username, password;

    cout << "Enter a username: ";
    cin >> username;

    cout << "Enter a password: ";
    cin >> password;

    ofstream outFile("accounts.txt", ios::app); 
    if (outFile.is_open()) {
        outFile << username << " " << password << endl;
        cout << "Account created successfully!" << endl;
        outFile.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void displayAccounts() {
    ifstream inFile("accounts.txt");
    string username, password;

    if (inFile.is_open()) {
        cout << "Accounts in the system:\n";
        while (inFile >> username >> password) {
            cout << "Username: " << username << ", Password: " << password << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void updateAccount() {
    string usernameToUpdate, newUsername, newPassword;
    cout << "Enter the username to update: ";
    cin >> usernameToUpdate;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt"); 
    string username, password;
    bool accountUpdated = false;

    if (inFile.is_open() && tempFile.is_open()) {
        while (inFile >> username >> password) {
            if (username == usernameToUpdate) {
                cout << "Enter new username: ";
                cin >> newUsername;
                cout << "Enter new password: ";
                cin >> newPassword;
                tempFile << newUsername << " " << newPassword << endl;
                accountUpdated = true;
            } else {
                tempFile << username << " " << password << endl;
            }
        }
        inFile.close();
        tempFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (accountUpdated) {
            cout << "Account updated successfully!" << endl;
        } else {
            cout << "Account not found." << endl;
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void deleteAccount() {
    string usernameToDelete;
    cout << "Enter the username to delete: ";
    cin >> usernameToDelete;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt"); 
    string username, password;
    bool accountDeleted = false;

    if (inFile.is_open() && tempFile.is_open()) {
        while (inFile >> username >> password) {
            if (username != usernameToDelete) {
                tempFile << username << " " << password << endl;
            } else {
                accountDeleted = true;
            }
        }
        inFile.close();
        tempFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (accountDeleted) {
            cout << "Account deleted successfully!" << endl;
        } else {
            cout << "Account not found." << endl;
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n====  Yokoso Watashino Soul Society ====" << endl;
        cout << "\n--- When you forgot your Account Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Read all Accounts (for testing purposes)\n";
        cout << "3. Update Account\n";
        cout << "4. Delete Account\n";
        cout << "5. Exit\n";
        cout << "==============================" << endl;
        cout << " Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                displayAccounts();
                break;
            case 3:
                updateAccount();
                break;
            case 4:
                deleteAccount();
                break;
            case 5:
                cout << "Exiting the program. Sayonara!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
