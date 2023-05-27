#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
    long type;
    char text[100];
};

int main()
{
    struct msgbuf message;

    key_t key = ftok(".", 2);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }
    int msqid = msgget(key, 0666);
    if (msqid == -1)
    {
        perror("msgget");
        exit(1);
    }
    if (msgrcv(msqid, &message, sizeof(message.text), 1, IPC_NOWAIT) == -1)
    {
        perror("msgrcv");
        exit(1);
    }

    printf("%s\n", message.text);

    msgctl(msqid, IPC_RMID, 0);

    return 0;
}