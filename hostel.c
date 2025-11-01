#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
struct Student {
    int studentID;
    char name[50];
    int roomNumber;
    char block;
    struct Student* next;
};

// Head pointer to the linked list
struct Student* head = NULL;

// Function to create a new student node
struct Student* createStudent(int id, char name[], int room, char block) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->studentID = id;
    strcpy(newStudent->name, name);
    newStudent->roomNumber = room;
    newStudent->block = block;
    newStudent->next = NULL;
    return newStudent;
}

// Add new allotment at the beginning
void addAllotment(int id, char name[], int room, char block) {
    struct Student* newStudent = createStudent(id, name, room, block);
    newStudent->next = head;
    head = newStudent;
    printf("Allotment added for %s\n", name);
}

// Remove a student by ID
void removeStudent(int id) {
    struct Student* temp = head;
    struct Student* prev = NULL;

    while (temp != NULL && temp->studentID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student ID %d not found.\n", id);
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Student ID %d removed from hostel.\n", id);
}

// Search by name or room number
void searchStudent(char* name, int room) {
    struct Student* temp = head;
    int found = 0;

    while (temp != NULL) {
        if ((name != NULL && strcmp(temp->name, name) == 0) || (room != -1 && temp->roomNumber == room)) {
            printf("Found: ID: %d, Name: %s, Room: %d, Block: %c\n", 
                temp->studentID, temp->name, temp->roomNumber, temp->block);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("No student found with the given criteria.\n");
}

// Display allotments block-wise
void displayBlockWise() {
    for (char block = 'A'; block <= 'Z'; block++) {
        struct Student* temp = head;
        int printed = 0;
        while (temp != NULL) {
            if (temp->block == block) {
                if (!printed) {
                    printf("\nBlock %c:\n", block);
                    printed = 1;
                }
                printf("  ID: %d, Name: %s, Room: %d\n", 
                    temp->studentID, temp->name, temp->roomNumber);
            }
            temp = temp->next;
        }
    }
}

// Reverse display using recursion
void reverseDisplay(struct Student* node) {
    if (node == NULL)
        return;
    reverseDisplay(node->next);
    printf("ID: %d, Name: %s, Room: %d, Block: %c\n", 
        node->studentID, node->name, node->roomNumber, node->block);
}

// Clone the linked list
struct Student* cloneList(struct Student* originalHead) {
    if (originalHead == NULL) return NULL;

    struct Student* newHead = createStudent(
        originalHead->studentID,
        originalHead->name,
        originalHead->roomNumber,
        originalHead->block
    );

    struct Student* currentOriginal = originalHead->next;
    struct Student* currentNew = newHead;

    while (currentOriginal != NULL) {
        currentNew->next = createStudent(
            currentOriginal->studentID,
            currentOriginal->name,
            currentOriginal->roomNumber,
            currentOriginal->block
        );
        currentOriginal = currentOriginal->next;
        currentNew = currentNew->next;
    }

    return newHead;
}

// Count students per block
void countPerBlock() {
    int blockCounts[26] = {0};
    struct Student* temp = head;

    while (temp != NULL) {
        if (temp->block >= 'A' && temp->block <= 'Z') {
            blockCounts[temp->block - 'A']++;
        }
        temp = temp->next;
    }

    printf("\nStudent Count per Block:\n");
    for (int i = 0; i < 26; i++) {
        if (blockCounts[i] > 0)
            printf("Block %c: %d student(s)\n", 'A' + i, blockCounts[i]);
    }
}

// Menu for operations
void menu() {
    printf("\n--- Student Hostel Allotment System ---\n");
    printf("1. Add Allotment\n");
    printf("2. Remove Student\n");
    printf("3. Search Student\n");
    printf("4. Display Allotments Block-wise\n");
    printf("5. Reverse Display\n");
    printf("6. Clone List\n");
    printf("7. Count Students per Block\n");
    printf("8. Exit\n");
    printf("Enter choice: ");
}

// Main function
int main() {
    int choice;

    do {
        menu();
        scanf("%d", &choice);
        if (choice == 1) {
            int id, room;
            char name[50], block;
            printf("Enter ID: "); scanf("%d", &id);
            printf("Enter Name: "); scanf(" %[^\n]", name);
            printf("Enter Room Number: "); scanf("%d", &room);
            printf("Enter Block (A-Z): "); scanf(" %c", &block);
            addAllotment(id, name, room, block);
        } else if (choice == 2) {
            int id;
            printf("Enter ID to remove: ");
            scanf("%d", &id);
            removeStudent(id);
        } else if (choice == 3) {
            char name[50];
            int room;
            printf("Enter Name (or '-' to skip): ");
            scanf(" %[^\n]", name);
            printf("Enter Room Number (-1 to skip): ");
            scanf("%d", &room);

            if (strcmp(name, "-") == 0)
                searchStudent(NULL, room);
            else
                searchStudent(name, room);
        } else if (choice == 4) {
            displayBlockWise();
        } else if (choice == 5) {
            printf("Reverse Display:\n");
            reverseDisplay(head);
        } else if (choice == 6) {
            struct Student* cloned = cloneList(head);
            printf("Cloned List (Reverse Display):\n");
            reverseDisplay(cloned);
        } else if (choice == 7) {
            countPerBlock();
        } else if (choice == 8) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 8);

    return 0;
}
