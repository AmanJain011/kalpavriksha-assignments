#include <stdio.h>
typedef struct
{
    unsigned int id;
    char name[20];
    unsigned char age;
} User;

static unsigned int ID = 1;

int generateUniqueID()
{
    return ID++;
}

void createNewUser()
{
    User user;
    FILE *fp;

    fp = fopen("users.txt", "a+");
    if (fp == NULL)
    {
        printf("\nError opening the file.\n");
        return;
    }

    printf("\nEnter User's Name : ");
    scanf("%s", &user.name);

    printf("\nEnter User's Age : ");
    scanf("%hhu", &user.age);
    if (user.age > 255)
    {
        printf("\nError: Age must be between 0 and 255.\n");
        fclose(fp);
        return;
    }

    user.id = generateUniqueID();

    fprintf(fp, "{\n  id: %d,\n  name: \"%s\",\n  age: %u\n},\n", user.id, user.name, user.age);

    fclose(fp);
}

void displayAllUsers()
{
    FILE *fp = fopen("users.txt", "r");
    printf("[");
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    printf("]");
    fclose(fp);
}

void updateUserById() {}

void deleteUserById() {}

int main()
{
    int choice;

    do
    {
        printf("\n1. Create A New User.");
        printf("\n2. Display All Users.");
        printf("\n3. Update User By ID.");
        printf("\n4. Delete User By ID.");
        printf("\n5. Exit");

        printf("\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createNewUser();
            break;

        case 2:
            displayAllUsers();
            break;

        case 3:
            updateUserById();
            break;

        case 4:
            deleteUserById();
            break;

        case 5:
            break;

        default:
            printf("\nInvalid Number.\n");
            break;
        }

    } while (choice != 5);

    return 0;
}