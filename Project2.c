/*
FriendZone: A text-based friend management app in C. Build your social circle!

Register and login: Create unique accounts with secure passwords.
Send and receive friend requests: Track pending requests and manage friendships.
Search for users: Find and connect with people you know.
Intuitive interface: Navigate easily with menus and simple prompts.
Bonus: Open-source, ready to grow! Contribute, improve, and shape your perfect friend circle!
Creator: Mohammed Rayaan Pasha.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for Friend Request
typedef struct FriendReq {
  int rear, front, size;
  char friendRequests[20][100];
} FriendReq;

// Struct for User
typedef struct User {
  char *username;
  char *password;
  FriendReq *friendList;
  char friends[20][100];
  int numFriends;
} User;

// Global Variables
User userDB[100];
User *myProfile = NULL;

// Hash Function
int hashcode(char *key) {
  int hash = 0;
  for (int i = 0; i < strlen(key); ++i) {
    hash = hash * 31 + key[i];
  }
  return hash % 100; // Adjust modulus based on actual user DB size
}

// Free allocated memory
void freeUser(User *user) {
  if (user) {
    free(user->username);
    free(user->password);
    if (user->friendList) {
      free(user->friendList);
    }
    free(user);
  }
}

// Register
void registerUser() {
  char choice;
  char username[50];
  char password[50];
  int duplicate;

  if (!myProfile) {
    while (1) {
      printf("Hello! To Register press 'r', To Login press 'l': ");
      scanf("%c", &choice);

      if (choice == 'r') {
        printf("Username: ");
        scanf("%s", username);
        int hash = hashcode(username);

        // Check for duplicate usernames
        duplicate = 0;
        for (int i = hash; i < hash + 2 && i < 100; ++i) {
          if (userDB[i].username && strcmp(userDB[i].username, username) == 0) {
            duplicate = 1;
            break;
          }
        }

        if (!duplicate) {
          if (!userDB[hash] && !userDB[hash + 1]) {
            // Allocate memory for new user
            userDB[hash] = malloc(sizeof(User));
            userDB[hash]->friendList = malloc(sizeof(FriendReq));
            myProfile = userDB[hash];
          } else if (!userDB[hash]) {
            userDB[hash + 1] = malloc(sizeof(User));
            userDB[hash + 1]->friendList = malloc(sizeof(FriendReq));
            myProfile = userDB[hash + 1];
          } else {
            printf("Database full!\n");
            return;
          }

          myProfile->username = strdup(username);
          printf("Enter password (minimum 8 characters): ");
          scanf("%s", password);
          if (strlen(password) < 8) {
            printf("Password too short, please try again.\n");
          } else {
            myProfile->password = strdup(password);
            myProfile->numFriends = 0;
            myProfile->friendList->rear = -1;
            myProfile->friendList->front = -1;
            myProfile->friendList->size = 20;
            printf("Welcome %s! Your profile is created.\n", myProfile->username);
            displayProfile();
            break;
          }
        } else {
          printf("Username already exists, try another.\n");
        }
      } else if (choice == 'l') {
        login();
        break;
      } else {
        printf("Invalid choice! Try again.\n");
      }
    }
  } else {
    printf("You are already logged in as %s.\n", myProfile->username);
  }
}

// Login
void login() {
  char username[50];
  char password[50];
  int hash;

  printf("Username: ");
  scanf("%s", username);
  hash = hashcode(username);

  if (userDB[hash].username && strcmp(userDB[hash].username, username) == 0) {
    myProfile = &userDB[hash];
  } else if (userDB[hash + 1].username && strcmp(userDB[hash + 1].username, username) == 0) {
    myProfile = &userDB[hash + 1];
  } else {
    printf("User not found. Please register or try again.\n");
    return;
  }

  printf("Password: ");
  scanf("%s", password);

  if (strcmp(myProfile->password, password) == 0) {
    printf("Welcome back, %s!\n", myProfile->username);
    displayProfile();
  } else {
    printf("Incorrect password. Please try again.\n");
    login();
  }
}

// Check if friend request list is full
int isFull(FriendReq *list) {
  return list->rear == list->size - 1;
}

// Check if friend request list is empty
int isEmpty(FriendReq *list) {
  return list->front == -1;
}

// Add friend request
void sendFriendRequest(User *toUser) {
  if (isFull(myProfile->friendList)) {
    printf("Your friend request list is full!\n");
    return;
  }

  myProfile->friendList->rear = (myProfile->friendList->rear + 1) % myProfile->friendList->size;
  myProfile->friendList->friendRequests[myProfile->friendList->rear] = toUser;
  printf("Friend request sent to %s!\n", toUser->username);
}

// Search for user
void searchUser() {
  char username[50];
  User *friend;

  while (1) {
    printf("Enter username: ");
    scanf("%s", username);

    int hash = hashcode(username);
    if (userDB[hash].username && strcmp(userDB[hash].username, username) == 0) {
      friend = &userDB[hash];
    } else if (userDB[hash + 1].username && strcmp(userDB[hash + 1].username, username) == 0) {
      friend = &userDB[hash + 1];
    } else {
      printf("User not found. Try again or enter 'b' to go back: ");
      char choice;
      scanf("%c", &choice);
      if (choice == 'b') {
        displayProfile();
        break;
      } else {
        continue;
      }
    }

    printf("%s found! Send friend request (y/n)? ", friend->username);
    char choice;
    scanf("%c", &choice);
    if (choice == 'y') {
      sendFriendRequest(friend);
      break;
    } else if (choice == 'n') {
      printf("Okay, going back.\n");
      break;
    } else {
      printf("Invalid choice. Try again.\n");
    }
  }
}

// View notifications (friend requests)
void viewNotifications() {
  if (isEmpty(myProfile->friendList)) {
    printf("You have no new friend requests.\n");
  } else {
    printf("Friend requests:\n");
    for (int i = myProfile->friendList->front + 1; i <= myProfile->friendList->rear; i++) {
      int index = i % myProfile->friendList->size;
      printf("- %s sent you a friend request.\n", userDB[index].username);
    }

    printf("Respond to requests (y/n)? ");
    char choice;
    scanf("%c", &choice);

    if (choice == 'y') {
      while (1) {
        printf("Enter username to respond to (or 'b' to go back): ");
        char username[50];
        scanf("%s", username);

        int found = 0;
        for (int i = myProfile->friendList->front + 1; i <= myProfile->friendList->rear; i++) {
          int index = i % myProfile->friendList->size;
          if (strcmp(userDB[index].username, username) == 0) {
            found = 1;
            User *friend = &userDB[index];

            printf("Accept (y) or reject (n) friend request from %s? ", friend->username);
            char response;
            scanf("%c", &response);
			
			if (response == 'y') {
              // Add friend to both lists
              for (int i = 0; i < myProfile->numFriends; ++i) {
                if (strcmp(myProfile->friends[i], friend->username) == 0) {
                  // Already friends, skip
                  break;
                }
              }
              if (myProfile->numFriends < 20) {
                strcpy(myProfile->friends[myProfile->numFriends], friend->username);
                myProfile->numFriends++;
              }

              for (int i = 0; i < friend->numFriends; ++i) {
                if (strcmp(friend->friends[i], myProfile->username) == 0) {
                  // Already friends, skip
                  break;
                }
              }
              if (friend->numFriends < 20) {
                strcpy(friend->friends[friend->numFriends], myProfile->username);
                friend->numFriends++;
              }

              // Remove friend request from list
              if (myProfile->friendList->front == myProfile->friendList->rear) {
                myProfile->friendList->front = -1;
                myProfile->friendList->rear = -1;
              } else {
                myProfile->friendList->front = (myProfile->friendList->front + 1) % myProfile->friendList->size;
              }
              printf("You are now friends with %s!\n", friend->username);
            } else if (response == 'n') {
              // Remove friend request from list
              if (myProfile->friendList->front == myProfile->friendList->rear) {
                myProfile->friendList->front = -1;
                myProfile->friendList->rear = -1;
              } else {
                myProfile->friendList->front = (myProfile->friendList->front + 1) % myProfile->friendList->size;
              }
              printf("Friend request from %s rejected.\n", friend->username);
            } else {
              printf("Invalid response. Try again.\n");
            }
            break;
          }
        }

        if (!found) {
          printf("User not found in your friend requests.\n");
        }

        printf("Respond to another request (y/n) or go back (b)? ");
        char choice2;
        scanf("%c", &choice2);

        if (choice2 == 'b') {
          break;
        } else if (choice2 != 'y') {
          printf("Going back.\n");
          break;
        }
      }
    } else if (choice == 'n') {
      printf("Okay, going back.\n");
    } else {
      printf("Invalid choice. Try again.\n");
    }
  }
}

// Display user profile options
void displayProfile() {
  char choice;

  while (1) {
    printf("\nWelcome, %s! Choose an option:\n", myProfile->username);
    printf("1. Search for users\n");
    printf("2. View friend requests\n");
    printf("3. Logout\n");

    scanf("%c", &choice);

    switch (choice) {
      case '1':
        searchUser();
        break;
      case '2':
        viewNotifications();
        break;
      case '3':
        printf("Logging out...\n");
        myProfile = NULL;
        displayMainMenu();
        break;
      default:
        printf("Invalid choice. Try again.\n");
        break;
    }
  }
}

// Display main menu before login
void displayMainMenu() {
  char choice;

  while (1) {
    printf("\nWelcome to the FriendZone!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

    scanf("%c", &choice);

    switch (choice) {
      case '1':
        registerUser();
        break;
      case '2':
        login();
        break;
      case '3':
        printf("Goodbye!\n");
        exit(0);
      default:
        printf("Invalid choice. Try again.\n");
        break;
    }
  }
}

int main() {
  // Initialize global variables
  for (int i = 0; i < 100; ++i) {
    userDB[i].username = NULL;
    userDB[i].password = NULL;
    userDB[i].friendList = NULL;
    for (int j = 0; j < 20; ++j) {
      userDB[i].friends[j][0] = '\0';
    }
    userDB[i].numFriends = 0;
  }

  // Display main menu
  displayMainMenu();

  // Free allocated memory before exiting
  for (int i = 0; i < 100; ++i) {
    freeUser(&userDB[i]);
  }

  return 0;
}
