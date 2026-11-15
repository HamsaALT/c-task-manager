#include <stdio.h>
#include <string.h>   

#define MAX_TASKS 100
#define MAX_LENGTH 100

// simple storage for tasks
char tasks[MAX_TASKS][MAX_LENGTH];
int taskCount = 0;

// load tasks from file when program starts
void loadTasks() {
    FILE *file = fopen("tasks.txt", "r");

    if (file == NULL) {
        // no file yet, nothing to load
        return;
    }

    while (fgets(tasks[taskCount], MAX_LENGTH, file)) {
        // remove newline from fgets
        tasks[taskCount][strcspn(tasks[taskCount], "\n")] = 0;
        taskCount++;
    }

    fclose(file);
}

// save tasks before exiting
void saveTasks() {
    FILE *file = fopen("tasks.txt", "w");

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n", tasks[i]);
    }

    fclose(file);
}

// add a new task
void addTask() {
    printf("Enter task: ");

    getchar(); // clears leftover input
    fgets(tasks[taskCount], MAX_LENGTH, stdin);

    // remove newline
    tasks[taskCount][strcspn(tasks[taskCount], "\n")] = 0;

    taskCount++;
}

// print all tasks
void showTasks() {
    if (taskCount == 0) {
        printf("No tasks yet\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

// delete a task by number
void deleteTask() {
    int index;

    printf("Task number: ");
    scanf("%d", &index);

    if (index < 1 || index > taskCount) {
        printf("Invalid number\n");
        return;
    }

    // shift tasks up
    for (int i = index - 1; i < taskCount - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }

    taskCount--;
}

int main() {
    int choice;

    loadTasks(); // load saved tasks

    while (1) {
        printf("\n=== TASK MANAGER (C) ===\n");
        printf("1. Add task\n");
        printf("2. Show tasks\n");
        printf("3. Delete task\n");
        printf("4. Exit\n");
        printf("Choose: ");

       if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // clear invalid input
        printf("Please enter a number\n");
        continue;
        }

        if (choice == 1) addTask();
        else if (choice == 2) showTasks();
        else if (choice == 3) deleteTask();
        else if (choice == 4) {
            saveTasks(); // save before closing
            break;
        } else {
            printf("Try again\n");
        }
    }

    return 0;
}
