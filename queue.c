#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent the queue
struct Queue {
    int array[MAX_SIZE];
    int front, rear;
};

// Function to initialize the queue
void initializeQueue(struct Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is full
int isFull(struct Queue *queue) {
    return (queue->rear == MAX_SIZE - 1);
}

// Function to check if the queue is empty
int isEmpty(struct Queue *queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Function to enqueue (push) an element into the queue
void enqueue(struct Queue *queue, int value) {
    if (isFull(queue)) {
        printf("Queue overflow!\n");
        return;
    }
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear++;
    queue->array[queue->rear] = value;
    printf("Enqueued %d into the queue\n", value);
}

// Function to dequeue (pop) an element from the queue
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow!\n");
        return -1; // Return a dummy value indicating underflow
    }
    int dequeued = queue->array[queue->front];
    queue->front++;
    if (queue->front > queue->rear)
        initializeQueue(queue);
    printf("Dequeued %d from the queue\n", dequeued);
    return dequeued;
}

// Function to display the elements of the queue
void display(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}

// Main function
int main() {
    struct Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    display(&queue);

    dequeue(&queue);
    dequeue(&queue);

    display(&queue);

    enqueue(&queue, 40);
    enqueue(&queue, 50);

    display(&queue);

    return 0;
}
