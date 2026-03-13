#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {

    struct user user, usr;
    char filename[100], phone[200], pword[50];
    int opt, choice;
    float amount;
    FILE *fp;

    printf("==== Welcome To Your Banking App ====\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("Choice: ");
    scanf("%d", &opt);

    /* ==== REGISTER ==== */
    if (opt == 1) {

        clearScreen();

        printf("Enter Account Number: ");
        scanf("%49s", user.ac);

        printf("Enter Phone Number: ");
        scanf("%49s", user.phone);

        printf("Enter Password: ");
        scanf("%49s", user.password);

        user.balance = 0;

        strcpy(filename, user.phone);
        strcat(filename, ".dat");

        fp = fopen(filename, "rb");
        if (fp != NULL) {
            printf("\nAccount already exists!\n");
            fclose(fp);
            return 0;
        }

        fp = fopen(filename, "wb");
        if (fp == NULL) {
            printf("Error creating account!\n");
            return 1;
        }

        fwrite(&user, sizeof(struct user), 1, fp);
        fclose(fp);

        printf("\nAccount Successfully Registered!\n");
    }

    /* ==== LOGIN ==== */
    else if (opt == 2) {

        clearScreen();

        printf("Phone Number: ");
        scanf("%49s", phone);

        printf("Password: ");
        scanf("%49s", pword);

        strcpy(filename, phone);
        strcat(filename, ".dat");

        fp = fopen(filename, "rb");
        if (fp == NULL) {
            printf("\nAccount Not Found!\n");
            return 0;
        }

        fread(&usr, sizeof(struct user), 1, fp);
        fclose(fp);

        if (strcmp(pword, usr.password) != 0) {
            printf("\nInvalid Password!\n");
            return 0;
        }

        /* ==== DASHBOARD LOOP ==== */
        while (1) {

            clearScreen();

            printf("\nWelcome %s\n", usr.phone);
            printf("1. Deposit\n");
            printf("2. Withdraw\n");
            printf("3. Transfer\n");
            printf("4. Check Balance\n");
            printf("5. Account Details\n");
            printf("6. Change Password\n");
            printf("7. Exit\n");
            printf("Choice: ");
            scanf("%d", &choice);

            switch (choice) {

                /* ===== Deposit ===== */
                case 1:
                    printf("Enter Amount: ");
                    scanf("%f", &amount);

                    if (amount <= 0) {
                        printf("Invalid amount!\n");
                        break;
                    }

                    usr.balance += amount;

                    fp = fopen(filename, "wb");
                    fwrite(&usr, sizeof(struct user), 1, fp);
                    fclose(fp);

                    printf("Deposited $%.2f Successfully!\n", amount);
                    break;

                /* ===== Withdraw ===== */
                case 2:
                    printf("Enter Amount: ");
                    scanf("%f", &amount);

                    if (amount <= 0) {
                        printf("Invalid amount!\n");
                        break;
                    }

                    if (amount > usr.balance) {
                        printf("Insufficient Balance!\n");
                        break;
                    }

                    usr.balance -= amount;

                    fp = fopen(filename, "wb");
                    fwrite(&usr, sizeof(struct user), 1, fp);
                    fclose(fp);

                    printf("Withdrawn $%.2f Successfully!\n", amount);
                    break;

                /* ===== Transfer ===== */
                case 3: {
                    char targetPhone[50], targetFile[60];
                    struct user targetUser;
                    FILE *ftp;

                    printf("Enter Recipient Phone: ");
                    scanf("%49s", targetPhone);

                    if (strcmp(targetPhone, usr.phone) == 0) {
                        printf("Cannot transfer to yourself!\n");
                        break;
                    }

                    printf("Enter Amount: ");
                    scanf("%f", &amount);

                    if (amount <= 0 || amount > usr.balance) {
                        printf("Invalid or insufficient balance!\n");
                        break;
                    }

                    strcpy(targetFile, targetPhone);
                    strcat(targetFile, ".dat");

                    ftp = fopen(targetFile, "rb+");
                    if (ftp == NULL) {
                        printf("Recipient not found!\n");
                        break;
                    }

                    fread(&targetUser, sizeof(struct user), 1, ftp);
                    targetUser.balance += amount;

                    fseek(ftp, 0, SEEK_SET);
                    fwrite(&targetUser, sizeof(struct user), 1, ftp);
                    fclose(ftp);

                    usr.balance -= amount;

                    fp = fopen(filename, "wb");
                    fwrite(&usr, sizeof(struct user), 1, fp);
                    fclose(fp);

                    printf("Transferred $%.2f Successfully!\n", amount);
                    break;
                }

                /* ===== Check Balance ===== */
                case 4:
                    printf("Current Balance: $%.2f\n", usr.balance);
                    break;

                /* ==== Account Details ==== */
                case 5:
                    printf("\n--- Account Details ---\n");
                    printf("Account No: %s\n", usr.ac);
                    printf("Phone No: %s\n", usr.phone);
                    printf("Balance: $%.2f\n", usr.balance);
                    break;

                /* ==== Change Password ==== */
                case 6:
                    printf("Enter New Password: ");
                    scanf("%49s", usr.password);

                    fp = fopen(filename, "wb");
                    fwrite(&usr, sizeof(struct user), 1, fp);
                    fclose(fp);

                    printf("Password Updated Successfully!\n");
                    break;

                case 7:
                    printf("Thank You for Using the App!\n");
                    exit(0);

                default:
                    printf("Invalid Choice!\n");
            }

            printf("\nPress Enter to continue...");
            getchar();
            getchar();
        }
    }

    else {
        printf("Invalid Option!\n");
    }

    return 0;
    }
