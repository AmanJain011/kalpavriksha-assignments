#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users.txt"
typedef struct {
  unsigned int id;
  char name[100];
  unsigned char age;
} User;

unsigned int generateUniqueID();
void createNewUser();
void displayAllUsers();
void updateUserById();
void deleteUserById();

int main() {
  int choice;

  do {
    printf("\n1. Create A New User.");
    printf("\n2. Display All Users.");
    printf("\n3. Update User By ID.");
    printf("\n4. Delete User By ID.");
    printf("\n5. Exit");
    printf("\nEnter Your Choice: ");
    scanf("%d", &choice);

    switch (choice) {
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

unsigned int generateUniqueID() {
  unsigned int lastId = 0;
  FILE *file = fopen(FILENAME, "r");
  if (file) {
    User user;
    while (fscanf(file, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3) {
      if (user.id > lastId)
        lastId = user.id;
    }
    fclose(file);
  }
  return lastId + 1;
}

void createNewUser() {
  User user;
  FILE *file = fopen(FILENAME, "a");
  if (file == NULL) return;

  printf("Enter User's Name: ");
  getchar();
  fgets(user.name, sizeof(user.name), stdin);
  user.name[strcspn(user.name, "\n")] = '\0';
  printf("Enter User's Age: ");
  int age;
  scanf("%d", &age);

  if (age > 255 || age < 0) {
    fclose(file);
    printf("\nAge should be between 0 to 255.\n");
    return;
  }

  user.id = generateUniqueID();
  fprintf(file, "%u|%s|%u\n", user.id, user.name, age);
  fclose(file);
  printf("User created successfully.\n");
}

void displayAllUsers() {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Error: File could not be opened.\n");
    return;
  }

  User user;
  printf("[\n");
  int first = 1;
  while (fscanf(file, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3) {
    if (!first) {
        printf(",\n");
    }
    printf("  {\n    \"id\": %u,\n    \"name\": \"%s\",\n    \"age\": %u\n  }", user.id, user.name, user.age);
    first = 0;
  }
  printf("\n]\n");
  fclose(file);
}

void updateUserById() {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Error: File could not be opened.\n");
    return;
  }

  int id, isUserFound = 0;
  printf("Enter the ID of the user to update: ");
  scanf("%d", &id);

  FILE *tempFile = fopen("temp.txt", "w");
  User user;

  while (fscanf(file, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3) {
    if (user.id == id) {
      isUserFound = 1;
      printf("Enter new name for user: ");
      getchar();
      fgets(user.name, sizeof(user.name), stdin);
      user.name[strcspn(user.name, "\n")] = '\0';
      printf("Enter new age for user: ");
      scanf("%hhu", &user.age);
    }
    fprintf(tempFile, "%u|%s|%u\n", user.id, user.name, user.age);
  }

  fclose(file);
  fclose(tempFile);

  if (isUserFound) {
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    printf("User with ID %d updated successfully.\n", id);
  } else {
    remove("temp.txt");
    printf("User not found with ID: %d.\n", id);
  }
}

void deleteUserById() {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Error: File could not be opened.\n");
    return;
  }

  int id, isUserFound = 0;
  printf("Enter the ID of the user to delete: ");
  scanf("%d", &id);

  FILE *tempFile = fopen("temp.txt", "w");
  User user;

  while (fscanf(file, "%u|%[^|]|%hhu\n", &user.id, user.name, &user.age) == 3) {
    if (user.id != id) {
      fprintf(tempFile, "%u|%s|%u\n", user.id, user.name, user.age);
    } else {
      isUserFound = 1;
    }
  }

  fclose(file);
  fclose(tempFile);

  if (isUserFound) {
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    printf("User with ID %d deleted successfully.\n", id);
  } else {
    remove("temp.txt");
    printf("User not found with ID: %d.\n", id);
  }
}