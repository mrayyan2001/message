#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>

// atoi string to integer

struct msgbuf
{
    long type;
    char text[100];
};

int main(int argc, char *argv[])
{

    struct msgbuf message;

    key_t key = ftok(".", 2);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1)
    {
        perror("msgget");
        exit(1);
    }

    message.type = 1;
    strcpy(message.text, "Message");

    if (msgsnd(msqid, &message, sizeof(message.text), IPC_NOWAIT) == -1)
    {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}