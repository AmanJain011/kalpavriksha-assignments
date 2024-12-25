#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#define FILENAME "users.txt"
typedef struct {
  unsigned int id;
  char name[100];
  int age;
} User;

unsigned int generateUniqueID();
void createNewUser();
void displayAllUsers();
void updateUserById();
void deleteUserById();
void displayMenu();
int getIntegerInput(const char *prompt, int min, int max);
int updateFile(const char *oldFileName, const char *newFileName, int isUserFound);
int removeFile(const char *fileName);
int renameFile(const char *oldFileName, const char *newFIleName);

int main() {
  int choice;

  do {
    displayMenu();
    choice = getIntegerInput("Enter a Choice (1-5): ", 1, 5);

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
    }
  } while (choice != 5);

  return 0;
}

int getIntegerInput(const char *prompt, int min, int max) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || value < min || value > max) {
        printf("Invalid number. Please enter a valid number: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return value;
}

void displayMenu(){
  printf("\n----------------------------");
  printf("\n1. Create A New User.");
  printf("\n2. Display All Users.");
  printf("\n3. Update User By ID.");
  printf("\n4. Delete User By ID.");
  printf("\n5. Exit\n");
}

unsigned int generateUniqueID() {
  unsigned int lastId = 0;
  FILE *file = fopen(FILENAME, "r");
  if (file) {
    User user;
    while (fscanf(file, "%u|%[^|]|%d\n", &user.id, user.name, &user.age) == 3) {
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
  fgets(user.name, sizeof(user.name), stdin);
  user.name[strcspn(user.name, "\n")] = '\0';

  user.age = getIntegerInput("Enter User's Age (0-200): ", 0, 200);

  user.id = generateUniqueID();
  fprintf(file, "%u|%s|%d\n", user.id, user.name, user.age);
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
  while (fscanf(file, "%u|%[^|]|%d\n", &user.id, user.name, &user.age) == 3) {
    if (!first) {
        printf(",\n");
    }
    printf("  {\n    \"id\": %u,\n    \"name\": \"%s\",\n    \"age\": %d\n  }", user.id, user.name, user.age);
    first = 0;
  }
  printf("\n]\n");
  fclose(file);
}

int updateFile(const char *oldFileName, const char *newFileName, int isUserFound) {
  if (isUserFound) {
    if (removeFile(oldFileName) != 0) {
      printf("Error in removing old file");
      return 0;
    }
    if (renameFile(newFileName, oldFileName) != 0) {
      printf("Error in renaming new file");
      return 0;
    }
    return 1;
  } else {
    remove(newFileName);
    printf("User not found.\n");
    return 0;
  }
}

void updateUserById() {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Error: File could not be opened.\n");
    return;
  }

  int id, isUserFound = 0;
  id = getIntegerInput("Enter the Id of the user to update: ", 0, INT_MAX);

  FILE *tempFile = fopen("temp.txt", "w");
  User user;

  while (fscanf(file, "%u|%[^|]|%d\n", &user.id, user.name, &user.age) == 3) {
    if (user.id == id) {
      isUserFound = 1;
      printf("Enter new name for user: ");
      fgets(user.name, sizeof(user.name), stdin);
      user.name[strcspn(user.name, "\n")] = '\0';
      printf("Enter new age for user: ");
      user.age = getIntegerInput("Enter new age for user (0-200): ", 0, 200);
    }
    fprintf(tempFile, "%u|%s|%d\n", user.id, user.name, user.age);
  }

  fclose(file);
  fclose(tempFile);

  int status = updateFile(FILENAME, "temp.txt", isUserFound);
  if(status){
    printf("User with ID %d updated successfully.\n", id);
  }
}

void deleteUserById() {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Error: File could not be opened.\n");
    return;
  }

  int id, isUserFound = 0;
  id = getIntegerInput("Enter the ID of the user to delete: ", 0, INT_MAX);

  FILE *tempFile = fopen("temp.txt", "w");
  User user;

  while (fscanf(file, "%u|%[^|]|%d\n", &user.id, user.name, &user.age) == 3) {
    if (user.id != id) {
      fprintf(tempFile, "%u|%s|%d\n", user.id, user.name, user.age);
    } else {
      isUserFound = 1;
    }
  }

  fclose(file);
  fclose(tempFile);

  int status = updateFile(FILENAME, "temp.txt", isUserFound);
  if(status){
    printf("User with ID %d deleted successfully.\n", id);
  }
}

int removeFile(const char *fileName){
  if(unlink(fileName) != 0){
    return 1;
  }
  return 0;
}

int renameFile(const char *oldFileName, const char *newFIleName) {
  FILE *oldFile = fopen(oldFileName, "r");
  FILE *newFile = fopen(newFIleName, "w");
  if (oldFile == NULL || newFile == NULL) {
    printf("Error: Failed to open files for copying.\n");
    return 1;
  }

  int ch;
  while ((ch = fgetc(oldFile)) != EOF) {
    fputc(ch, newFile);
  }

  fclose(oldFile);
  fclose(newFile);

  if(removeFile(oldFileName)){
    printf("Error in file removing.\n");
    return 1;
  };

  return 0;
}