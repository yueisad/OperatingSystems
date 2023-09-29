#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOWER_CYLINDER 0
#define UPPER_CYLINDER 4999

// Function to read requests from the file request.txt
void readRequests(int **requests, int *num_requests) {
    FILE *file;
    file = fopen("request.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    int size = 10;
    int *arr = (int *)malloc(size * sizeof(int));

    int num;
    int index = 0;

    while (fscanf(file, "%d", &num) == 1) {
        if (index == size) {
            size *= 2;
            arr = (int *)realloc(arr, size * sizeof(int));
        }
        if (num < LOWER_CYLINDER) {
            num = LOWER_CYLINDER;
        } else if (num > UPPER_CYLINDER) {
            num = UPPER_CYLINDER;
        }
        arr[index++] = num;
    }

    fclose(file);

    *requests = arr;
    *num_requests = index;
}

// Function to perform FCFS (First-Come-First-Serve) scheduling algorithm
int fcfs(int *requests, int num_requests, int initial_position) {
    int head_movement = 0;
    int current_position = initial_position;

    printf("FCFS: %d", current_position);

    for (int i = 0; i < num_requests; i++) {
        int next_position = requests[i];

        head_movement += abs(next_position - current_position);
        current_position = next_position;

        printf(", %d", current_position);
    }

    printf("\nTotal head movement: %d\n", head_movement);
    return head_movement;
}

// Function to perform SSTF (Shortest-Seek-Time-First) scheduling algorithm
int sstf(int *requests, int num_requests, int initial_position) {
    int head_movement = 0;
    int current_position = initial_position;

    bool *processed = (bool *)calloc(num_requests, sizeof(bool));

    printf("\nSSTF: %d", current_position);

    for (int i = 0; i < num_requests; i++) {
        int min_distance = UPPER_CYLINDER - LOWER_CYLINDER + 1;
        int next_index = -1;

        for (int j = 0; j < num_requests; j++) {
            if (!processed[j]) {
                int distance = abs(requests[j] - current_position);
                if (distance < min_distance) {
                    min_distance = distance;
                    next_index = j;
                }
            }
        }

        head_movement += min_distance;
        current_position = requests[next_index];
        processed[next_index] = true;

        printf(", %d", current_position);
    }

    printf("\nTotal head movement: %d\n", head_movement);
    free(processed);
    return head_movement;
}

// Function to sort the requests array
void sortRequests(int *requests, int num_requests) {
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = i+1; j < num_requests; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}

// Function to perform SCAN scheduling algorithm
int scan(int *requests, int num_requests, int initial_position) {
    int head_movement = 0;
    int current_position = initial_position;

    // Sort the requests array in ascending order
    sortRequests(requests, num_requests);

    printf("\nSCAN: %d", current_position);

    int start_index = 0;
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= current_position) {
            start_index = i;
            break;
        }
    }

     // Head movement towards the end
    for (int i = start_index; i < num_requests; i++) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }


    // Head movement back to the beginning
    head_movement += abs(UPPER_CYLINDER - current_position);
    current_position = UPPER_CYLINDER;

    
    // Head movement back to the beginning
    for (int i = start_index - 1; i >= 0; i--) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }

    printf("\nTotal head movement: %d\n", head_movement);
    return head_movement;
}

// Function to perform C-SCAN scheduling algorithm
int cscan(int *requests, int num_requests, int initial_position) {
    int head_movement = 0;
    int current_position = initial_position;

    // Sort the requests array in ascending order
    sortRequests(requests, num_requests);

    printf("\nC-SCAN: %d", current_position);

    int start_index = 0;
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= current_position) {
            start_index = i;
            break;
        }
    }

    // Head movement towards the end
    for (int i = start_index; i < num_requests; i++) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }

    // Head movement to the end cylinder
    head_movement += abs(UPPER_CYLINDER - current_position);
    current_position = UPPER_CYLINDER;
    

    // Head movement back to the start cylinder
    head_movement += abs(UPPER_CYLINDER - LOWER_CYLINDER);
    current_position = LOWER_CYLINDER;
    

    // Continue head movement towards the start (excluding processed requests)
    for (int i = 0; i < start_index; i++) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }

    printf("\nTotal head movement: %d\n", head_movement);
    return head_movement;
}

// Function to perform LOOK scheduling algorithm
int look(int *requests, int num_requests, int initial_position) {
    int head_movement = 0;
    int current_position = initial_position;

    // Sort the requests array in ascending order
    sortRequests(requests, num_requests);

    printf("\nLOOK: %d", current_position);

    int start_index = 0;
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= current_position) {
            start_index = i;
            break;
        }
    }

    // Head movement towards the end
    for (int i = start_index; i < num_requests; i++) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }

    // Head movement back to the beginning
    for (int i = start_index - 1; i >= 0; i--) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }

    printf("\nTotal head movement: %d\n", head_movement);
    return head_movement;
}

// Function to perform C-LOOK scheduling algorithm
int clook(int *requests, int num_requests, int initial_position) {
    int head_movement = 0;
    int current_position = initial_position;

    // Sort the requests array in ascending order
    sortRequests(requests, num_requests);

    printf("\nC-LOOK: %d", current_position);

    int start_index = 0;
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= current_position) {
            start_index = i;
            break;
        }
    }

    // Head movement towards the end
    for (int i = start_index; i <= num_requests-1; i++) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }


    // Continue head movement towards the start
    for (int i = 0; i < start_index; i++) {
        int next_position = requests[i];
        head_movement += abs(next_position - current_position);
        current_position = next_position;
        printf(", %d", current_position);
    }


    printf("\nTotal head movement: %d\n", head_movement);
    return head_movement;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <initial_position>\n", argv[0]);
        return 1;
    }

    int initial_position = atoi(argv[1]);
    if (initial_position < LOWER_CYLINDER || initial_position > UPPER_CYLINDER) {
        printf("Initial cylinder position must be between %d and %d.\n", LOWER_CYLINDER, UPPER_CYLINDER);
        return 1;
    }

    int *requests;
    int num_requests;

    // Read requests from the file
    readRequests(&requests, &num_requests);

    // Execute FCFS algorithm
    fcfs(requests, num_requests, initial_position);

    // Execute SSTF algorithm
    sstf(requests, num_requests, initial_position);

    // Execute SCAN algorithm
    scan(requests, num_requests, initial_position);

    // Execute C-SCAN algorithm
    cscan(requests, num_requests, initial_position);

    // Execute LOOK algorithm
    look(requests, num_requests, initial_position);

    // Execute C-LOOK algorithm
    clook(requests, num_requests, initial_position);

    // Clean up
    free(requests);

    return 0;
}
