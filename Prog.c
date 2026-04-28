#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 5  

typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}


bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}


bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}


void writeBuffer(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow! Cannot insert '%c'\n", data);
        return;
    }

    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

char readBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow!\n");
        return '\0';
    }

    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;

    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[100];
    char finalText[200];

    printf("Enter your name: ");
    scanf("%99s", name);

    strcpy(finalText, name);
    strcat(finalText, "CE-ESY");

    printf("\nFinal Text: %s\n", finalText);

    printf("\n--- Writing to Circular Buffer ---\n");

    for (int i = 0; i < strlen(finalText); i++) {

        if (isFull(&cb)) {
            char removed = readBuffer(&cb);
            printf("Read to free space: %c\n", removed);
        }

        writeBuffer(&cb, finalText[i]);
        printf("Inserted: %c\n", finalText[i]);
    }

    printf("\n--- Reading Remaining Data ---\n");

    while (!isEmpty(&cb)) {
        printf("%c", readBuffer(&cb));
    }

    printf("\n\nBuffer is now empty.\n");

    return 0;
}
