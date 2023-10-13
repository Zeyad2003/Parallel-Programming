#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User {
    char firstName[30];
    char lastName[30];
    char username[30];
    char password[20];
};

void registration() {
    FILE *reg;

    reg = fopen("reg.txt", "w");
    if (reg == nullptr) {
        fputs("Error at opening File!", stderr);
        return;
    }

    struct User u{};

    printf("\nEnter First Name: ");
    fgets(u.firstName, 30, stdin);
    u.firstName[strcspn(u.firstName, "\n")] = '\0';

    printf("\nEnter last name: ");
    fgets(u.lastName, 30, stdin);
    u.lastName[strcspn(u.lastName, "\n")] = '\0';

    printf("\nEnter Username: ");
    fgets(u.username, 30, stdin);
    u.username[strcspn(u.username, "\n")] = '\0';

    printf("\nEnter Password: ");
    fgets(u.password, 20, stdin);
    u.password[strcspn(u.password, "\n")] = '\0';

    fwrite(&u, sizeof(u), 1, reg);
    fclose(reg);

    printf("\nRegistration Successful!!\n");
    printf("Press enter to continue!!'\n");
    getchar();
}

void login() {
    struct User u{};
    char username[30], password[20];
    FILE *reg;

    reg = fopen("reg.txt", "r");
    if (reg == nullptr) {
        fputs("Error at opening File!!", stderr);
        return;
    }

    printf("\nEnter your credentials, please.");
    printf("\nUsername: ");
    fgets(username, 30, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("\nPassword: ");
    fgets(password, 20, stdin);
    password[strcspn(password, "\n")] = '\0';

    while (fread(&u, sizeof(u), 1, reg)) {
        if (strcmp(username, u.username) == 0 && strcmp(password, u.password) == 0) {
            printf("\nSuccessful Login!!\n");
            printf("Hello, %s %s\n", u.firstName, u.lastName);
        } else {
            printf("\nWrong Username or Password\n");
        }
    }

    fclose(reg);
}

int main() {
    char input[10];
    int num;

    while (true) {
        printf("Press '1' to Register");
        printf("\nPress '2' to Login");
        printf("\nPress '3' to close the application\n");

        fgets(input, 10, stdin);

        num = strtol(input, nullptr, 10);

        if (num == 1) {
            registration();
        } else if (num == 2) {
            login();
            return 0;
        } else if (num == 3) {
            printf("Bye Bye!!\n");
            return 0;
        } else {
            printf("Invalid Input. Try again:\n");
        }
    }
}
