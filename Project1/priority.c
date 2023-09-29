#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[3];
    int priority;
    int burst;
} Task;

void swapTasks(Task* task1, Task* task2) {
    Task temp = *task1;
    *task1 = *task2;
    *task2 = temp;
}

void sortTasks(Task tasks[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                swapTasks(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

void executeTasks(Task tasks[], int n) {
    int i;
    printf("Process\tPriority\tBurst\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\n", tasks[i].name, tasks[i].priority, tasks[i].burst);
    }
}

int main() {
    Task tasks[20];
    int n = 0;

    FILE* file = fopen("schedule.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ", ");
        strcpy(tasks[n].name, token);

        token = strtok(NULL, ", ");
        tasks[n].priority = atoi(token);

        token = strtok(NULL, ", ");
        tasks[n].burst = atoi(token);

        n++;
    }

    fclose(file);

    sortTasks(tasks, n);

    executeTasks(tasks, n);

    return 0;
}
