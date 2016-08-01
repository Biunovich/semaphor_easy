#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
typedef struct mymsgbuf
{
	long mtype;
	char name[20];
	key_t key;
	char str[100];
} mymsgbuf;