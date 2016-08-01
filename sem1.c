#include "mylib.h"
void main()
{
	char str[100];
	struct sembuf sops;
	key_t key = ftok("/home/buin/sem",'a');
	int shmid = shmget(key,256,IPC_CREAT | 0777);
	char *shmaddr = shmat(shmid,NULL,0);
	int semid = semget(key,1,IPC_CREAT | 0777);
	semctl(semid,0,IPC_SET,0);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	while(str[0] != 'q')
	{
		printf("ENTER STRING: ");
		scanf("%s",str);
		strcpy(shmaddr,str);
		sops.sem_op = 1;
		semop(semid,&sops,1);
	}
	shmdt(shmaddr);
	semctl(semid,0,IPC_RMID,0);
	shmctl(shmid,IPC_RMID,NULL);
}