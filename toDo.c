#include <stdio.h>
#include <string.h>

#define MAX_TODOS 10
#define MAX_TODO_LENGTH 100

// Function Prototypes
void addTodo(char todoList[MAX_TODOS][MAX_TODO_LENGTH], int *count, int completed[]);
void deleteTodo(char todoList[MAX_TODOS][MAX_TODO_LENGTH], int *count, int completed[]);
void markTodoCompleted(int completed[], int count);
void displayTodos(char todoList[MAX_TODOS][MAX_TODO_LENGTH], int count, int completed[]);

int main() {
    char todoList[MAX_TODOS][MAX_TODO_LENGTH];  // Array to store the to-do items
    int completed[MAX_TODOS] = {0};  // Array to keep track of completed items
    int count = 0;  // Keeps track of the number of to-do items
    int choice;

    printf("Welcome to the To-Do List App!\n");

    // Main menu loop
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add To-Do\n");
        printf("2. Delete To-Do\n");
        printf("3. Mark To-Do as Completed\n");
        printf("4. Display To-Do List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear the input buffer

        switch (choice) {
            case 1:
                addTodo(todoList, &count, completed);
                break;
            case 2:
                deleteTodo(todoList, &count, completed);
                break;
            case 3:
                markTodoCompleted(completed, count);
                break;
            case 4:
                displayTodos(todoList, count, completed);
                break;
            case 5:
                printf("Exiting the application. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add a to-do item
void addTodo(char todoList[MAX_TODOS][MAX_TODO_LENGTH], int *count, int completed[]) {
    if (*count >= MAX_TODOS) {
        printf("The to-do list is full! You can't add more items.\n");
        return;
    }

    printf("Enter a new to-do item (max %d characters): ", MAX_TODO_LENGTH - 1);
    fgets(todoList[*count], MAX_TODO_LENGTH, stdin);

    // Remove the newline character at the end of the input
    size_t len = strlen(todoList[*count]);
    if (len > 0 && todoList[*count][len - 1] == '\n') {
        todoList[*count][len - 1] = '\0';
    }

    completed[*count] = 0;  // Mark the new to-do as not completed
    (*count)++;

    printf("To-Do item added!\n");
}

// Function to delete a to-do item
void deleteTodo(char todoList[MAX_TODOS][MAX_TODO_LENGTH], int *count, int completed[]) {
    if (*count == 0) {
        printf("The to-do list is empty! Nothing to delete.\n");
        return;
    }

    int index;
    printf("Enter the number of the to-do item to delete (1-%d): ", *count);
    scanf("%d", &index);
    while (getchar() != '\n');  // Clear the input buffer

    if (index < 1 || index > *count) {
        printf("Invalid index! Please try again.\n");
        return;
    }

    index--;  // Convert to zero-based index

    // Shift items to the left to fill the gap
    for (int i = index; i < *count - 1; i++) {
        strcpy(todoList[i], todoList[i + 1]);
        completed[i] = completed[i + 1];
    }

    (*count)--;
    printf("To-Do item deleted!\n");
}

// Function to mark a to-do item as completed
void markTodoCompleted(int completed[], int count) {
    if (count == 0) {
        printf("The to-do list is empty! Nothing to mark as completed.\n");
        return;
    }

    int index;
    printf("Enter the number of the to-do item to mark as completed (1-%d): ", count);
    scanf("%d", &index);
    while (getchar() != '\n');  // Clear the input buffer

    if (index < 1 || index > count) {
        printf("Invalid index! Please try again.\n");
        return;
    }

    index--;  // Convert to zero-based index

    completed[index] = 1;
    printf("To-Do item marked as completed!\n");
}

// Function to display the to-do list
void displayTodos(char todoList[MAX_TODOS][MAX_TODO_LENGTH], int count, int completed[]) {
    if (count == 0) {
        printf("The to-do list is empty!\n");
        return;
    }

    printf("Current To-Do List:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s [%s]\n", i + 1, todoList[i], completed[i] ? "Completed" : "Pending");
    }
}
