#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long type;
    char text[80];
};

int main() {
    key_t key = ftok("key.txt", 65); // Use the same key
    int queueId = msgget(key, 0666 | IPC_CREAT);

    struct message msg;
    msg.type = 1; // Set message type

    // Prepare and send a message
    strcpy(msg.text, "Hello from the message queue!");
    msgsnd(queueId, &msg, sizeof(msg.text), 0);

    printf("Message sent to the queue.\n");
    return 0;
}
