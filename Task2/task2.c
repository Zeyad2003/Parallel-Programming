#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20

struct User {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    int isActive;
};

union LoginOrRegister {
    struct {
        char username[USERNAME_LENGTH];
        char password[PASSWORD_LENGTH];
    } login;

    struct {
        char username[USERNAME_LENGTH];
        char password[PASSWORD_LENGTH];
    } registerUser;
};

struct User userAccounts[MAX_USERS];

void registerUser(union LoginOrRegister *data) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(userAccounts[i].username, data->registerUser.username) == 0) {
            printf("Username already taken. Please choose another username.\n");
            return;
        }
    }

    for (int i = 0; i < MAX_USERS; ++i) {
        if (!userAccounts[i].isActive) {
            strcpy(userAccounts[i].username, data->registerUser.username);
            strcpy(userAccounts[i].password, data->registerUser.password);
            userAccounts[i].isActive = 1;
            printf("Registration successful. Welcome, %s!\n", data->registerUser.username);
            return;
        }
    }

    printf("User limit reached. Cannot register new user.\n");
}

void loginUser(union LoginOrRegister *data) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (userAccounts[i].isActive &&
            strcmp(userAccounts[i].username, data->login.username) == 0 &&
            strcmp(userAccounts[i].password, data->login.password) == 0) {
            printf("Login successful. Welcome back, %s!\n", data->login.username);
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
}

int main() {
    union LoginOrRegister userAction;

    strcpy(userAction.registerUser.username, "Zeyad2003");
    strcpy(userAction.registerUser.password, "zeyad");
    registerUser(&userAction);

    strcpy(userAction.login.username, "Zeyad2003");
    strcpy(userAction.login.password, "zeyad");
    loginUser(&userAction);

    return 0;
}


