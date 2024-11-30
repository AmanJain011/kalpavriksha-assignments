#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "users.txt"

typedef struct
{
    unsigned int id;
    char name[100];
    unsigned char age;
} User;

unsigned int generateUniqueID()
{
    unsigned int lastID = 0;
    FILE *fp = fopen(FILENAME, "r");
    if (fp)
    {
        User user;
        while (fscanf(fp, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3)
        {
            if (user.id > lastID)
                lastID = user.id;
        }
        fclose(fp);
    }
    return lastID + 1;
}

void createNewUser()
{
    User user;
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL)
        return;

    printf("Enter User's Name: ");
    getchar();
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    printf("Enter User's Age: ");
    scanf("%hhu", &user.age);

    if (user.age > 255)
    {
        fclose(fp);
        return;
    }

    user.id = generateUniqueID();
    fprintf(fp, "%u|%s|%u\n", user.id, user.name, user.age);
    fclose(fp);
    printf("User created successfully.\n");
}

void displayAllUsers()
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    User user;
    printf("[\n");
    int first = 1;
    while (fscanf(fp, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3)
    {
        if (!first)
            printf(",\n");
        printf("  {\n    \"id\": %u,\n    \"name\": \"%s\",\n    \"age\": %u\n  }", user.id, user.name, user.age);
        first = 0;
    }
    printf("\n]\n");
    fclose(fp);
}

void updateUserById()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("File is empty; updation is not possible.\n");
        return;
    }

    int id, found = 0;
    printf("Enter the ID of the user to update: ");
    scanf("%d", &id);

    FILE *temp = fopen("temp.txt", "w");
    User user;

    while (fscanf(file, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3)
    {
        if (user.id == id)
        {
            found = 1;
            printf("Enter new name for user: ");
            getchar();
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = '\0';
            printf("Enter new age for user: ");
            scanf("%hhu", &user.age);
        }
        fprintf(temp, "%u|%s|%u\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User with ID %d updated successfully.\n", id);
    }
    else
    {
        remove("temp.txt");
        printf("User not found with ID: %d.\n", id);
    }
}

void deleteUserById()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("File is empty; deletion is not possible.\n");
        return;
    }

    int id, found = 0;
    printf("Enter the ID of the user to delete: ");
    scanf("%d", &id);

    FILE *temp = fopen("temp.txt", "w");
    User user;

    while (fscanf(file, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3)
    {
        if (user.id != id)
        {
            fprintf(temp, "%u|%s|%u\n", user.id, user.name, user.age);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User with ID %d deleted successfully.\n", id);
    }
    else
    {
        remove("temp.txt");
        printf("User not found with ID: %d.\n", id);
    }
}

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
        printf("\nEnter Your Choice: ");
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
            printf("Invalid Number.\n");
            break;
        }
    } while (choice != 5);

    return 0;
}
