#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define FILENAME "db.txt"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

struct User {
    char username[50];
    int userType;
    double balance;
    long long mobileNumber;
};

struct User users[MAX_USERS];
int userCount = 0;

void loadUsersFromFile();
void appendUserToFile(const struct User user);
void saveUsersToFile();
void allUsers();
void performTransaction(const long long senderPhoneNumber, const long long receiverPhoneNumber, double amount);
void checkBalance(const long long phoneNumber);
void addMoney(const long long phoneNumber, double amount);
void cashOut(const long long phoneNumber, double amount);
void createAccount();
int findUserByPhoneNumber(const long long phoneNumber);

int main() {
    loadUsersFromFile();
    char inputUsername[50];
    char inputPassword[50];
    printf("Admin Login\n");
    printf("Username: ");
    scanf("%s", inputUsername);
    printf("Password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, ADMIN_USERNAME) != 0 || strcmp(inputPassword, ADMIN_PASSWORD) != 0) {
        printf(" Invalid Username or Password\n");
        return 1;
    }

    int choice;
    do {
        printf("Admin Panel\n");
        printf("1. Create new account\n");
        printf("2. Check balance\n");
        printf("3. Add money\n");
        printf("4. Send money\n");
        printf("5. Make payment\n");
        printf("6. Cashout\n");
        printf("7. Show All Users\n");
        printf("0. Log out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2: {
                long long phoneNumber;
                printf("Enter phone number: ");
                scanf("%lld", &phoneNumber);
                checkBalance(phoneNumber);
                break;
            }
            case 3: {
                long long phoneNumber;
                double amount;
                printf("Enter phone number: ");
                scanf("%lld", &phoneNumber);
                printf("Enter amount to add: ");
                scanf("%lf", &amount);
                addMoney(phoneNumber, amount);
                break;
            }
            case 4: {
                long long senderPhoneNumber;
                long long receiverPhoneNumber;
                double amount;
                printf("Enter sender phone number: ");
                scanf("%lld", &senderPhoneNumber);

                int senderIndex = findUserByPhoneNumber(senderPhoneNumber);
                if (senderIndex == -1) {
                    printf("Sender account not found.\n");
                    break;
                }

                if (users[senderIndex].userType != 1) {
                    printf("Sender is not a customer.\n");
                    break;
                }
                printf("Enter receiver phone number: ");
                scanf("%lld", &receiverPhoneNumber);
                int receiverIndex = findUserByPhoneNumber(receiverPhoneNumber);
                if (receiverIndex == -1) {
                    printf("Receiver account not found.\n");
                    break;
                }
                if (users[receiverIndex].userType != 1) {
                    printf("Receiver is not a customer.\n");
                    break;
                }
                printf("Enter amount to send: ");
                scanf("%lf", &amount);
                performTransaction(senderPhoneNumber, receiverPhoneNumber, amount);
                break;
            }
            case 5: {
                long long customerPhoneNumber;
                long long merchantPhoneNumber;
                double amount;
                printf("Enter customer phone number: ");
                scanf("%lld", &customerPhoneNumber);
                int customerIndex = findUserByPhoneNumber(customerPhoneNumber);
                if (customerIndex == -1) {
                    printf("Sender account not found.\n");
                    break;
                }
                if (users[customerIndex].userType != 1) {
                    printf("Sender is not a customer.\n");
                    break;
                }
                printf("Enter merchant phone number: ");
                scanf("%lld", &merchantPhoneNumber);
                int merchantIndex = findUserByPhoneNumber(merchantPhoneNumber);
                if (merchantIndex == -1) {
                    printf("Merchant account not found.\n");
                    break;
                }
                if (users[merchantIndex].userType != 0) {
                    printf("This is not a merchant number.\n");
                    break;
                }
                printf("Enter amount for payment: ");
                scanf("%lf", &amount);
                performTransaction(customerPhoneNumber, merchantPhoneNumber, amount);
                break;
            }
            case 6: {
                long long phoneNumber;
                double amount;
                printf("Enter phone number: ");
                scanf("%lld", &phoneNumber);
                int customerIndex = findUserByPhoneNumber(phoneNumber);
                if (customerIndex == -1) {
                    printf("account not found.\n");
                    break;
                }
                printf("Enter amount to cash out: ");
                scanf("%lf", &amount);
                cashOut(phoneNumber, amount);
                break;
            }
            case 7: {
                allUsers();
                break;
            }
            case 0:
                printf("Logging out.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}

void loadUsersFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        file = fopen(FILENAME, "w");
        if (file == NULL) {
            printf("Error\n");
        }
    }

    while (fscanf(file, "%s %d %lf %lld", users[userCount].username, &users[userCount].userType,
                  &users[userCount].balance, &users[userCount].mobileNumber) != EOF) {
        userCount++;
        if (userCount >= MAX_USERS) {
            printf("Maximum user limit reached.\n");
            break;
        }
    }

    fclose(file);
}

void appendUserToFile(const struct User user) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error\n");
        return;
    }
    fprintf(file, "%s %d %.2lf %lld\n", user.username, user.userType,
            user.balance, user.mobileNumber);

    fclose(file);
}

void saveUsersToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error\n");
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %d %.2lf %lld\n", users[i].username, users[i].userType,
                users[i].balance, users[i].mobileNumber);
    }

    fclose(file);
}

void performTransaction(const long long senderPhoneNumber, const long long receiverPhoneNumber, double amount) {
    int senderIndex = findUserByPhoneNumber(senderPhoneNumber);
    int receiverIndex = findUserByPhoneNumber(receiverPhoneNumber);

    printf("Amount = %f Sender Number = %lld\t balance = %.2lf \n", amount, senderPhoneNumber,
           users[senderIndex].balance);

    if (users[senderIndex].balance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    users[senderIndex].balance -= amount;
    users[receiverIndex].balance += amount;
    saveUsersToFile();
    printf("Transaction successful.\n");
}

void checkBalance(const long long phoneNumber) {
    int userIndex = findUserByPhoneNumber(phoneNumber);

    if (userIndex == -1) {
        printf("User with the given phone number not found.\n");
        return;
    }

    printf("Balance: %.2lf\n", users[userIndex].balance);
}

void addMoney(const long long phoneNumber, double amount) {
    int userIndex = findUserByPhoneNumber(phoneNumber);

    if (userIndex == -1) {
        printf("User with the given phone number not found.\n");
        return;
    }

    users[userIndex].balance += amount;
    saveUsersToFile();
    printf("Money added successfully.\n");
}

void createAccount() {
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        return;
    }

    struct User newUser;
    printf("Enter username: ");
    scanf(" %[^\n]", newUser.username);
    for (int i = 0; newUser.username[i]; i++) {
    if (newUser.username[i] == ' ') {
        newUser.username[i] = '_';
    }
    }
    printf("Enter user type (0 for merchant, 1 for customer): ");
    scanf("%d", &newUser.userType);

    int mobileNumberExists = 0;
    do {
        printf("Enter mobile number: ");
        scanf("%lld", &newUser.mobileNumber);

        mobileNumberExists = 0;
        for (int i = 0; i < userCount; i++) {
            if (newUser.mobileNumber == users[i].mobileNumber) {
                printf("Mobile number already exists. Please enter a different mobile number.\n");
                mobileNumberExists = 1;
                break;
            }
        }
    } while (mobileNumberExists);

    printf("Enter initial balance: ");
    scanf("%lf", &newUser.balance);

    users[userCount] = newUser;
    userCount++;
    appendUserToFile(newUser);

    printf("Account created successfully\n");
}

void cashOut(const long long phoneNumber, double amount) {
    int userIndex = findUserByPhoneNumber(phoneNumber);
    if (userIndex == -1) {
        printf("User with the given phone number not found.\n");
        return;
    }

    if (amount > users[userIndex].balance) {
        printf("Insufficient balance\n");
        return;
    }
    users[userIndex].balance -= amount;
    saveUsersToFile();
    printf("Cash out successful.\n");
}

void allUsers() {
    printf("All Users\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("Username\t\t\tUser Type\tBalance\t\tMobile Number\n");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < userCount; i++) {
        char usernameWithSpaces[50]; 
        for (int j = 0; users[i].username[j]; j++) {
            if (users[i].username[j] == '_') {
                usernameWithSpaces[j] = ' ';
            } else {
                usernameWithSpaces[j] = users[i].username[j];
            }
        }
        usernameWithSpaces[strlen(users[i].username)] = '\0';
        const char *userTypeString = (users[i].userType == 1) ? "Personal" : "Merchant";
        printf("%s\t\t%-10s\t%-10.2lf\t0%lld\n", usernameWithSpaces, userTypeString,
               users[i].balance, users[i].mobileNumber);
        printf("---------------------------------------------------------------------------------\n");
    }
}

int findUserByPhoneNumber(const long long phoneNumber) {
    for (int i = 0; i < userCount; i++) {
        if (phoneNumber == users[i].mobileNumber) {
            return i;
        }
    }
    return -1;
}