#include <stdio.h>
#include <string.h>

#define MAX 100  // Maximum queue size

struct Call {
    int id;
    char callerName[50];
    char issue[200];
};

// Array-based queue
struct CallQueue {
    struct Call calls[MAX];
    int front;
    int rear;
};

void initialize(struct CallQueue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct CallQueue *q) {
    return (q->front == -1 || q->front > q->rear);
}

int isFull(struct CallQueue *q) {
    return (q->rear == MAX - 1);
}

void enqueue(struct CallQueue *q, struct Call c) {
    if (isFull(q)) {
        printf("Queue is full! Cannot receive new call.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->calls[q->rear] = c;
    printf("Call added to queue.\n");
}

struct Call dequeue(struct CallQueue *q) {
    struct Call c;
    if (isEmpty(q)) {
        printf("Queue is empty! No calls to handle.\n");
        c.id = -1;
        return c;
    }
    c = q->calls[q->front];
    q->front++;
    return c;
}

void display(struct CallQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current Calls in Queue:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("ID: %d, Caller: %s\n", q->calls[i].id, q->calls[i].callerName);
    }
}

// Function to receive call
struct Call receiveCall(int id) {
    struct Call c;
    c.id = id;

    printf("Enter caller name: ");
    scanf("%s", c.callerName);

    printf("Enter issue description: ");
    getchar(); // clear newline from buffer
    fgets(c.issue, sizeof(c.issue), stdin);

    // Remove trailing newline from fgets
    c.issue[strcspn(c.issue, "\n")] = '\0';

    return c;
}

// Handle call
void handleCall(struct Call c) {
    if (c.id == -1) return;
    printf("\nHandling Call ID: %d\n", c.id);
    printf("Caller: %s\n", c.callerName);
    printf("Issue: %s\n", c.issue);
    printf("Call handled successfully!\n\n");
}

int main() {
    struct CallQueue callQueue;
    initialize(&callQueue);

    int choice;
    int callID = 1;

    while (1) {
        printf("\n=== Call Center Menu ===\n");
        printf("1. Receive Call\n");
        printf("2. Handle Call\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Call c = receiveCall(callID++);
                enqueue(&callQueue, c);
                break;
            }
            case 2: {
                struct Call c = dequeue(&callQueue);
                handleCall(c);
                break;
            }
            case 3:
                display(&callQueue);
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}